using System;
using System.Net;

using OpenHome.Soundcard;

    class Program : IReceiverHandler
    {
        public static void Main(string[] args)
        {
            Program program = new Program();

            program.Run();
        }

        public void Run()
        {
            bool enabled = true;

            Soundcard soundcard = new Soundcard(IPAddress.Any, 1, 1, false, enabled, 99, this);

            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);

                if (key.KeyChar == 'q')
                {
                    break;
                }

                if (key.KeyChar == 'e')
                {
                    if (enabled)
                    {
                        enabled = false;
                        Console.WriteLine("Disabled");
                    }
                    else
                    {
                        enabled = true;
                        Console.WriteLine("Enabled");
                    }

                    soundcard.SetEnabled(enabled);
                    
                    continue;
                }
            }

            soundcard.Dispose();
        }

        public void ReceiverAdded(IReceiver aReceiver)
        {
            Console.WriteLine("Added   {0}:{1}:{2}:{3}", aReceiver.Room, aReceiver.Group, aReceiver.Name, aReceiver.Status);
        }

        public void ReceiverChanged(IReceiver aReceiver)
        {
            Console.WriteLine("Changed {0}:{1}:{2}:{3}", aReceiver.Room, aReceiver.Group, aReceiver.Name, aReceiver.Status);
        }

        public void ReceiverRemoved(IReceiver aReceiver)
        {
            Console.WriteLine("Removed {0}:{1}:{2}:{3}", aReceiver.Room, aReceiver.Group, aReceiver.Name, aReceiver.Status);
        }
    }
