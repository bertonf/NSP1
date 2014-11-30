#include "middleware.h"

Middleware::Middleware()
{
}

void Middleware::run()
{
    _capture.SetNetworkInterface("wlan0");
    _capture.start();
    while(1)
    {
        if (_capture.isListEmpty() == false)
            _mainWindow.AddRow(_capture.GetTopPacketList());
        
    }

}

void Middleware::ShowWindow()
{
    _mainWindow.InitInterfaces(_interface.GetInterfaces());
    _mainWindow.show();

}
