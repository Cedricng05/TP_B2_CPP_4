#include <windows.h>
#include <string>
#ifndef CONFIG_H
#define CONFIG_H

using namespace std;

class Config
{
    public:
        Config();
        void create();
        void readRecord();
        void onlyThat();
        virtual ~Config();

    protected:

    private:

};

#endif // CONFIG_H
