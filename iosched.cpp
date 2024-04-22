#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <deque>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
#include <unistd.h>

using namespace std; 

string filepath;
char schedulerType = 'N';

struct IOEvent { 
    int id = 0; 
    int issueTime = 0; 
    int track = 0;
    int trackPrev = 0;
    int startTime = 0;
    int endTime = 0;
    int distance = 0;
};

deque<IOEvent*> IOTable;
vector<IOEvent*> results;

struct IOScheduler { 
    int currentTime = 0;
    int startTime = 0;
    int endTime = 0;
    int finishTime = 0;

    int distance = 0;

    int track = 0;
    int trackPrev = 0;          

    bool turnaround = false;

    int maxTrack = 0; 
    int minTrack = numeric_limits<int>::max();  

    char schedulerType;     

    void update(IOEvent* IO) {   
        IO->trackPrev = trackPrev;
        IO->startTime = max(IO->issueTime, currentTime);
        IO->distance = abs(IO->track - IO->trackPrev);
        IO->endTime = IO->startTime + IO->distance;     
        finishTime = IO->endTime;               
        trackPrev = IO->track;
        results[IO->id] = IO;        
    }    
    
    void printResults() { 
        int waitTime = 0;  
        long int waitTimeTotal = 0;  
        int waitTimeMax = 0;       
        long int distanceTotal = 0;   
        long int tatTotal = 0;
        int numRequests = 0;
        double waitTimeAvg = 0; 
        double tatAvg = 0;   
        double IOUtil = 0;  

        for (IOEvent* IO: results) { 
            printf("%5d: %5d %5d %5d\n", 
                   IO->id, 
                   IO->issueTime,
                   IO->startTime, 
                   IO->endTime);  

            waitTime = IO->startTime - IO->issueTime;
            waitTimeTotal += waitTime;
            waitTimeMax = max(waitTime, waitTimeMax);
            distanceTotal += IO->distance;
            tatTotal += (IO->endTime - IO->issueTime);                  
            numRequests++;
        }
        
        IOUtil = static_cast<double>(distanceTotal) / finishTime;
        tatAvg = static_cast<double>(tatTotal) / numRequests;
        waitTimeAvg = static_cast<double>(waitTimeTotal) / numRequests;

        printf("SUM: %d %d %.4lf %.2lf %.2lf %d\n",
               finishTime, 
               distanceTotal, 
               IOUtil, 
               tatAvg, 
               waitTimeAvg, 
               waitTimeMax);          
    }        
};

struct FIFO: public IOScheduler { 
    void strategy() { 
        int selectedID = 0;
        while (!IOTable.empty()) {  
            IOEvent* IO = IOTable[selectedID];
            IOTable.erase(IOTable.begin() + selectedID);  
            update(IO);
            currentTime = IO->endTime;
        }
        printResults();     
    };    
};


struct LOOK: public IOScheduler { 
    int selectedID = 0;
    int seekTime = 0;
    int issueTime = 0;
    int upCount = 0;
    int downCount = 0;
    int minSeekTime = numeric_limits<int>::max();
    string direction = "up";

    int up() { 
        minSeekTime = numeric_limits<int>::max();
        upCount = 0;
        maxTrack = 0;
        minTrack = numeric_limits<int>::max();        
        
        for (int id = 0; id < IOTable.size(); id++) { 
            issueTime = IOTable[id]->issueTime;

            if (issueTime <= currentTime) { 
                track = IOTable[id]->track;

                maxTrack = max(maxTrack, track);
                minTrack = min(minTrack, track);                 

                if (track >= trackPrev) { 
                    seekTime = track - trackPrev;
                    upCount++;

                    if (seekTime < minSeekTime) { 
                        minSeekTime = seekTime;
                        selectedID = id;
                    }
                }
            }

            else if (issueTime > currentTime) {      
                break;
            }
        }
        return selectedID;        
    }

    int down() { 
        minSeekTime = numeric_limits<int>::max();
        downCount = 0;

        for (int id = 0; id < IOTable.size(); id++) { 
            issueTime = IOTable[id]->issueTime;        

            if (issueTime <= currentTime) { 
                track = IOTable[id]->track;
                if (track <= trackPrev) { 
                    seekTime = abs(track - trackPrev);
                    downCount++;

                    if (seekTime < minSeekTime) { 
                        minSeekTime = seekTime;
                        selectedID = id;    
                    }
                }
            }
            else if (issueTime > currentTime) { 
                break;
            }
        }
        return selectedID;
    };   
  
    void strategy() { 
        while (!IOTable.empty()) {   
            upCount = 0;
            downCount = 0;
            
            if (direction == "up") { 
                selectedID = up();
                if (upCount == 0) { 
                    direction = "down";
                    selectedID = down();
                }                
            }
            
            else if (direction == "down") {
                selectedID = down();
                if (downCount == 0) { 
                    direction = "up";
                    selectedID = up();                               
                }         
            }

            if (upCount == 0 && downCount == 0) { 
                track = IOTable[selectedID]->track;
                if (direction == "up" &&  track < trackPrev) { 
                    direction = "down";
                    selectedID = down();
                }

                else if (direction == "down" && track > trackPrev) { 
                    direction = "up";
                    selectedID = up();
                }                
            }   

            IOEvent* IO = IOTable[selectedID];
            IOTable.erase(IOTable.begin() + selectedID);  
            update(IO);
            currentTime = IO->endTime;
        } 
        printResults();         
    }
};

struct SSTF: public IOScheduler { 
    void strategy() { 
        int seekTime = 0;
        int issueTime = 0;
        int selectedID = 0;
        
        while (!IOTable.empty()) { 
            int minSeekTime = numeric_limits<int>::max();

            for (int id = 0; id < IOTable.size(); id++) { 
                issueTime = IOTable[id]->issueTime;
                
                if (issueTime <= currentTime) { 
                    track = IOTable[id]->track;
                    seekTime = abs(track - trackPrev);

                    if (seekTime < minSeekTime) {
                        minSeekTime = seekTime;
                        selectedID = id;
                    }
                }
                else if (issueTime > currentTime) {      
                    break;
                }                
            }

            IOEvent* IO = IOTable[selectedID];
            IOTable.erase(IOTable.begin() + selectedID);  
            update(IO);
            currentTime = IO->endTime;
        } 

        printResults();         
    }
};

struct CLOOK: public LOOK { 
    int selectedID = 0;
    int issueTime = 0;
    int seekTime = 0;
 
    string direction = "up";

    void strategy() { 
        while (!IOTable.empty()) {   
            selectedID = up();

            if (upCount == 0) {  
                for (int id = 0; id < IOTable.size(); id++) { 
                    if (turnaround) { 
                        if (IOTable[id]->track <= minTrack) { 
                            turnaround = false;
                            selectedID = id;
                            break;
                        }
                    }
                }      
            }   
               
            IOEvent* IO = IOTable[selectedID];
            IOTable.erase(IOTable.begin() + selectedID);
            update(IO);

            currentTime = IO->endTime;

            if (IO->track >= maxTrack) { 
                turnaround = true;
            }
            else { 
                turnaround = false;
            }                
                      
        } 
        printResults();       
    }
};

struct FLOOK: public LOOK { 
    vector<IOEvent*> activeQ;
    vector<IOEvent*> addQ;
    vector<int> seekTimeList;
    string direction = "up";

    int up() { 
        upCount = 0;
        selectedID = 0;
        minSeekTime = numeric_limits<int>::max(); 
        for (size_t i = 0; i < seekTimeList.size(); i++) {
            if (seekTimeList[i] >= 0) {
                upCount++;
                if (seekTimeList[i] < minSeekTime) {
                    selectedID = i;
                    minSeekTime = seekTimeList[i];
                }
            }
        }
        return selectedID;
    };

    int down() { 
        downCount = 0;
        selectedID = 0;
        minSeekTime = numeric_limits<int>::max(); 

        for (size_t i = 0; i < seekTimeList.size(); i++) {
            if (seekTimeList[i] <= 0) { 
                downCount++;
                if (abs(seekTimeList[i]) < minSeekTime) {
                    selectedID = i;
                    minSeekTime = abs(seekTimeList[i]);
                }
            }
        }     
        return selectedID;       
    }    
    
    void strategy() {   
        int activeEndTime = 0;
        bool active = false;
        
        while (!(IOTable.empty() && activeQ.empty() && addQ.empty())) { 

            if (!IOTable.empty()) {
                IOEvent* IO = IOTable.front();

                if (IO->issueTime > currentTime) {
                    if (!active) {
                        currentTime = IO->issueTime;
                    }
                }

                if (IO->issueTime <= currentTime) {
                    IO->trackPrev = trackPrev;
                    IO->distance = IO->track - IO->trackPrev;
                    IOTable.pop_front();
                    addQ.push_back(IO);
                }
            }

            if (active) {
                if (currentTime < activeEndTime) {
                    currentTime++;
                } 
                else if (currentTime >= activeEndTime) {
                    active = false;
                }
            }

            if (activeQ.empty() && !active) { 
                activeQ.insert(activeQ.end(), 
                               make_move_iterator(addQ.begin()),
                               make_move_iterator(addQ.end()));
                addQ.clear();
            }               
            

            if (!activeQ.empty() && !active) { 
                
                seekTimeList.clear();

                for (int id = 0; id < activeQ.size(); id++) { 
                    seekTime = activeQ[id]->distance;
                    seekTimeList.push_back(seekTime);
                }
                
                if (direction == "up") { 
                    selectedID = up();
                    if (upCount == 0) { 
                        direction = "down";
                        selectedID = down();
                    }         
                }

                else if (direction == "down") { 
                    selectedID = down();
                    if (downCount == 0) { 
                        direction = "up";
                        selectedID = up();
                    }                                                    
                }                

                IOEvent* selectedIO = activeQ[selectedID];
                activeQ.erase(activeQ.begin() + selectedID);

                update(selectedIO);   

                for (IOEvent* activeIO: activeQ) { 
                    activeIO->trackPrev = selectedIO->track;
                    activeIO->distance = activeIO->track - activeIO->trackPrev;
                }         

                for (IOEvent* addIO: addQ) { 
                    addIO->trackPrev = selectedIO->track;
                    addIO->distance = addIO->track - addIO->trackPrev;
                }      
                                
                activeEndTime = selectedIO->startTime + abs(selectedIO->distance); 
                active = true;  
            }
        }        
        printResults();
    }
};


int main(int argc, char* argv[]) {  
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1) { 
        switch(opt) { 
            case 's': 
                schedulerType = optarg[0]; 
                break;                                
        }
    }
    filepath = argv[optind];

    ifstream input(filepath);
    string line; 
    int id = 0; 
    int maxTrack = 0;
    int minTrack = numeric_limits<int>::max();
        
    while (getline(input, line)) { 
        if (line[0] != '#') { 
            int timeStep;
            int track;
            stringstream lineSplit(line);
            if (lineSplit >> timeStep >> track) { 
                IOEvent* IO = new IOEvent;
                IO->id = id;
                IO->issueTime = timeStep;
                IO->track = track;
                IOTable.push_back(IO);
                id++;              
            }
        }
    }

    results.resize(IOTable.size());

    if (schedulerType == 'N') { 
        FIFO scheduler;
        scheduler.schedulerType = schedulerType;
        scheduler.strategy();
    }
    else if (schedulerType == 'S') { 
        SSTF scheduler;
        scheduler.schedulerType = schedulerType;
        scheduler.strategy();        
    }
    else if (schedulerType == 'L') { 
        LOOK scheduler;
        scheduler.schedulerType = schedulerType;
        scheduler.strategy();        
    }
    else if (schedulerType == 'C') { 
        CLOOK scheduler;
        scheduler.schedulerType = schedulerType;
        scheduler.strategy();        
    }
    else if (schedulerType == 'F') { 
        FLOOK scheduler;
        scheduler.schedulerType = schedulerType;
        scheduler.strategy(); 
    }

    IOTable.clear();    

    for (int i = 0; i < IOTable.size(); i++) {
        delete &IOTable[i];
    }

    input.close();
}