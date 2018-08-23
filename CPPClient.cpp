//
#include "clientproxylibrary.h"
#include <iostream>
#include <glib.h>

cbool TheCallBack()
	{
		std::cout<< "Inside Callback" <<std::endl;
		return 1;
	}
	
cbool res = 1;
int in=-1;
std::string sin="";
std::string ain="";
std::string aon="";
	
void* MenuLoop(void* data)
	{
		int running=1;
		while(running)
		{
			std::cout<< "1.Set time" <<std::endl;
			std::cout<< "2.Set alarm time"<<std::endl;
			std::cout<< "3.Set alarm status" <<std::endl;
			std::cout<< "4.Display alarm status" <<std::endl;
			std::cout<< "5.Exit" <<std::endl;
			std::cin>> in ;
			if(in <1 && in > 5)
				{
					std::cout<<"Please chose a number between 1 & 5" << std::endl;
				}
			else if(in==1)
				{
					std::cout<< "What is the time ? Ex: 0100 / 1400 / 2335" <<std::endl;
					std::cin>>sin;
					SetTime(sin.data());
					std::cout<< "Time set to:" + sin <<std::endl;
				}
			else if(in==2)
				{
					std::cout<< "What is the alarm time ? Ex: 0110 / 1401 / 2340" <<std::endl;
					std::cin>>ain;
					SetAlarmTime(ain.data());
					std::cout<< "Time set to:" + ain <<std::endl;
				}
			else if(in==3)
				{
					std::cout<< "Turn alarm on/off ?" <<std::endl;
					std::cin>>aon;
					if(aon == "on" || aon == "ON" || aon == "On")
						{
						SetAlarmStatus(1);
						std::cout<< "Alarm is ON" <<std::endl;
						}
					else if(aon == "off" || aon == "OFF" || aon == "Off")
						{
						SetAlarmStatus(0);
						std::cout<< "Alarm is OFF"<<std::endl;
						}
					else
						std::cout<< "Please type on or off" << std::endl;
				}
			else if(in==4)
				{
					GetAlarmStatus(&res);
				
					std::cout<<"Alarm is:"<< res << std::endl;
				}
			else if(in==5)
				{
					g_main_loop_quit(static_cast<GMainLoop*>(data));
					running=0;
				}
			
		}
		g_thread_exit(NULL);
		return NULL;
	}
	
int main()
{	
	init();
	
	GMainLoop *MainLoop = g_main_loop_new(NULL,FALSE);
    if(MainLoop == NULL)
    {
        std::cout<<"GMainLoop failed\n";
    }
    std::cout<<"starting gmain loop\n";
    
    GThread* Menuthread = g_thread_new("MenuThread",&MenuLoop,MainLoop);
    
    OnSignalRecieve(&TheCallBack);
    
    g_main_loop_run(MainLoop);
    std::cout<<"before join\n";
    g_thread_join(Menuthread);
	std::cout<<"after join\n";
}
