#ifndef RECORDS_H
#define RECORDS_H
#include<string>

#include <iostream>

class record {

	private:
            double FT;
            int PID;
            int QT;
            double WT;
            std::string status;
            static int count;

public:
    record(double ft = 0, int pid = 0, int qt = 0, double wt = 0, std::string status = "");

    double getFT()   const;
    int getPID() const;
    int getQT() const;
    double getWT() const;
    std::string getStatus() const;
    static const int getcount();
    static void setcount(int x);
    


    
};
#endif

