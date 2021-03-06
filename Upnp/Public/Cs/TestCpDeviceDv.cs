using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;
using OpenHome.Net.Device;

namespace OpenHome.Net
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams
            {
                MsearchTimeSecs = 1,
                UseLoopbackNetworkInterface = true
            };
            Library lib = new Library();
            lib.Initialise(initParams);
            lib.StartCombined();

            Console.Write("TestCpDeviceDvCs - starting\n");
            DeviceBasic device = new DeviceBasic();
            CpDeviceDv cpDevice = new CpDeviceDv(device.Device());
            TestBasicCp cp = new TestBasicCp(cpDevice);
            cp.TestActions();
            cp.TestSubscriptions();
            cpDevice.RemoveRef();
            device.Dispose();
            Console.Write("TestCpDeviceDvCs - completed\n");
            
            lib.Close();
        }
    }
}
