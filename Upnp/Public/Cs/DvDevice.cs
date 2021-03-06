using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;

namespace OpenHome.Net.Device
{
    /// <summary>
    /// Interface passed to implementors of DvDevice allowing them to serve UI files to Control Points
    /// </summary>
    public interface IResourceWriter
    {
        /// <summary>
        /// Must be called before writing any file data
        /// </summary>
        /// <param name="aTotalBytes">Size in bytes of the file.  Can be 0 if size is unknown.</param>
        /// <param name="aMimeType">MIME type of the file.  May be NULL if this is unknown.</param>
        void WriteResourceBegin(int aTotalBytes, string aMimeType);
        /// <summary>
        /// Called to write a block of file data
        /// </summary>
        /// <remarks>Will be called 0..n times after WriteResourceBegin and before WriteResourceEnd</remarks>
        /// <param name="aData">File data to write</param>
        /// <param name="aBytes">Size in bytes of aData</param>
        void WriteResource(byte[] aData, int aBytes);
        /// <summary>
        /// Called when serving of a file is complete
        /// </summary>
        /// <remarks>Must only be called after a call to WriteResourceBegin.
        /// 
        /// An error writing the file can be inferred if WriteResource has not been called or
        /// if aTotalBytes was non-zero in the WriteResourceBegin callback and the sum of aBytes
        /// values in the WriteResource callbacks does not match aTotalBytes.</remarks>
        void WriteResourceEnd();
    }

    /// <summary>
    /// Interface used by devices to publish data (typically files)
    /// </summary>
    public interface IResourceManager
    {
        void WriteResource(string aUriTail, uint aIpAddress, List<string> aLanguageList, IResourceWriter aWriter);
    }

    /// <summary>
    /// Helper class for writing resources (files) to native code
    /// </summary>
    /// @internal
    class ResourceWriter : IResourceWriter
    {
        private IntPtr iWriterData;
        private DvDeviceStandard.CallbackWriteResourceBegin iWriteBegin;
        private DvDeviceStandard.CallbackWriteResource iWriteResource;
        private DvDeviceStandard.CallbackWriteResourceEnd iWriteEnd;

        public ResourceWriter(IntPtr aWriterData,
                              DvDeviceStandard.CallbackWriteResourceBegin aWriteBegin,
                              DvDeviceStandard.CallbackWriteResource aWriteResource,
                              DvDeviceStandard.CallbackWriteResourceEnd aWriteEnd)
        {
            iWriterData = aWriterData;
            iWriteBegin = aWriteBegin;
            iWriteResource = aWriteResource;
            iWriteEnd = aWriteEnd;
        }

        public void Write(IResourceManager aManager, string aUriTail, uint aInterface, List<string> aLanguageList)
        {
            aManager.WriteResource(aUriTail, aInterface, aLanguageList, this);
        }                              
        
        public unsafe void WriteResourceBegin(int aTotalBytes, string aMimeType)
        {
            char* mimeType = (char*)Marshal.StringToHGlobalAnsi(aMimeType).ToPointer();
            iWriteBegin(iWriterData, aTotalBytes, mimeType);
            Marshal.FreeHGlobal((IntPtr)mimeType);
        }

        public void WriteResource(byte[] aData, int aBytes)
        {
            iWriteResource(iWriterData, aData, aBytes);
        }

        public void WriteResourceEnd()
        {
            iWriteEnd(iWriterData);
        }
    }

    /// <summary>
    /// A factory to create DvDevices.
    /// </summary>
    public interface IDvDeviceFactory
    {
        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.DvDevice CreateDevice(string aUdn);

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn);

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files.</param>
        OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn, IResourceManager aResourceManager);
    }

    /// <summary>
    /// The default factory for DvDevices. Creates devices normally.
    /// </summary>
    public class DvDeviceFactory : IDvDeviceFactory
    {
        private OpenHome.Net.Core.DeviceStack iDeviceStack;

        /// <summary>
        /// Create a new device factory. Requires a running device stack.
        /// </summary>
        public DvDeviceFactory(OpenHome.Net.Core.DeviceStack aDeviceStack)
        {
            iDeviceStack = aDeviceStack;
            if (iDeviceStack == null)
            {
                throw new ArgumentNullException("aDeviceStack");
            }
        }

        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        public OpenHome.Net.Device.DvDevice CreateDevice(string aUdn)
        {
            return new DvDevice(aUdn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        public OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn)
        {
            return new DvDeviceStandard(aUdn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files</param>
        public OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn, IResourceManager aResourceManager)
        {
            return new DvDeviceStandard(aUdn, aResourceManager);
        }
    }
    
    public class DvDevice : IDisposable
    {
        [DllImport("ohNet")]
        static extern unsafe IntPtr DvDeviceCreate(char* aUdn);
        [DllImport("ohNet")]
        static extern void DvDeviceDestroy(IntPtr aDevice);
        [DllImport("ohNet")]
        static extern unsafe char* DvDeviceUdn(IntPtr aDevice);
        [DllImport("ohNet")]
        static extern int DvDeviceEnabled(IntPtr aDevice);
        [DllImport("ohNet")]
        static extern void DvDeviceSetEnabled(IntPtr aDevice);
        [DllImport("ohNet")]
        static extern unsafe void DvDeviceSetDisabled(IntPtr aDevice, System.Action<IntPtr> aCompleted, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern unsafe void DvDeviceGetAttribute(IntPtr aDevice, char* aKey, char** aValue);
        [DllImport("ohNet")]
        static extern unsafe void DvDeviceSetAttribute(IntPtr aDevice, char* aKey, char* aValue);
        [DllImport("ohNet")]
        static extern unsafe void DvDeviceSetXmlExtension(IntPtr aDevice, char* aXml);
        [DllImport("ohNet")]
        static extern unsafe void OhNetFree(void* aPtr);

        protected IntPtr iHandle;
        protected GCHandle iGch;

        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        public unsafe DvDevice(string aUdn)
        {
            char* udn = (char*)Marshal.StringToHGlobalAnsi(aUdn).ToPointer();
            iHandle = DvDeviceCreate(udn);
            Marshal.FreeHGlobal((IntPtr)udn);
        }

        protected DvDevice()
        {
        }

        /// <summary>
        /// Query the (client-specified) unique device name
        /// </summary>
        /// <returns>The name passed to the c'tor</returns>
        public unsafe String Udn()
        {
            IntPtr ip = (IntPtr)DvDeviceUdn(iHandle);
            String udn = Marshal.PtrToStringAnsi(ip);
            return udn;
        }
        
        /// <summary>
        /// Query whether a device is enabled
        /// </summary>
        /// <returns>true if the device is enabled; false otherwise</returns>
        public bool Enabled()
        {
            int enabled = DvDeviceEnabled(iHandle);
            if (enabled != 0)
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Set the device ready for external use
        /// </summary>
        /// <remarks>When this returns, the device will be available for use using any of the protocols
        /// the device stack supports.  Services must not be added (DvProvider-derived classes
        /// created using this device) and attributes must not be set while a device is enabled.
        /// If these need to change in future, the device must first be disabled.</remarks>
        public void SetEnabled()
        {
            DvDeviceSetEnabled(iHandle);
        }

        /// <summary>
        /// Disable the device, withdrawing its availability for external use
        /// </summary>
        /// <remarks>Services can be added and attributes can be set once a device is disabled.  The device
        /// will not be available for use again until SetEnabled() is called again.
        /// 
        /// This call is asynchronous so returns before the device is fully disabled.  Wait for the
        /// aCompleted callback before adding services or setting attributes.</remarks>
        /// <param name="aCompleted">Callback which runs when the device is fully disabled.
        /// Until this runs, the device should be considered to still be enabled.</param>
        public void SetDisabled(Action aCompleted)
        {
            GCHandle gch = GCHandle.Alloc(aCompleted);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            DvDeviceSetDisabled(iHandle, Disabled, ptr);
        }

        private static void Disabled(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            System.Action cb = (System.Action)gch.Target;
            gch.Free();
            cb();
        }
        
        /// <summary>
        /// Query the value of an atrribute
        /// </summary>
        /// <param name="aKey">string of the form protocol_name.protocol_specific_key.
        /// Commonly used keys are published ... (!!!! where?)</param>
        /// <param name="aValue">string containing the attribute or null if the attribute has not been set.</param>
        public unsafe void GetAttribute(string aKey, out string aValue)
        {
            char* key = (char*)Marshal.StringToHGlobalAnsi(aKey).ToPointer();
            char* value;
            DvDeviceGetAttribute(iHandle, key, &value);
            Marshal.FreeHGlobal((IntPtr)key);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
        }
        
        /// <summary>
        /// Set the value of an attribute
        /// </summary>
        /// <param name="aKey">string of the form protocol_name.protocol_specific_key</param>
        /// <param name="aValue">attribute will be set to a copy of this string</param>
        public unsafe void SetAttribute(string aKey, string aValue)
        {
            char* key = (char*)Marshal.StringToHGlobalAnsi(aKey).ToPointer();
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            DvDeviceSetAttribute(iHandle, key, value);
            Marshal.FreeHGlobal((IntPtr)key);
            Marshal.FreeHGlobal((IntPtr)value);
        }

        /// <summary>
        /// Add a block of xml which will be returned as part of the device description
        /// </summary>
        /// <remarks>Use is limited to UPnP for now.  Xml is returned with device xml inside the 'device'
        /// tag (at the same level as most attributes)</remarks>
        /// <param name="aXml">One or more tag+value blocks</param>
        public unsafe void SetXmlExtension(string aXml)
        {
            char* xml = (char*)Marshal.StringToHGlobalAnsi(aXml).ToPointer();
            DvDeviceSetXmlExtension(iHandle, xml);
            Marshal.FreeHGlobal((IntPtr)xml);
        }

        /// <summary>
        /// Get the handle to the underlying native device
        /// </summary>
        /// <returns>Handle to the underlying native device</returns>
        public IntPtr Handle()
        {
            return iHandle;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvDevice()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvDeviceDestroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }

    public class DvDeviceStandard : DvDevice
    {
        [DllImport("ohNet")]
        static extern unsafe IntPtr DvDeviceStandardCreateNoResources(char* aUdn);
        [DllImport("ohNet")]
        static extern unsafe IntPtr DvDeviceStandardCreate(char* aUdn, CallbackResourceManager aResourceManager, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern unsafe uint DvResourceWriterLanguageCount(IntPtr aHandle);
        [DllImport("ohNet")]
        static extern unsafe IntPtr DvResourceWriterLanguage(IntPtr aHandle, uint aIndex);

        public unsafe delegate void CallbackWriteResourceBegin(IntPtr aPtr, int aTotalBytes, char* aMimeType);
        public delegate void CallbackWriteResource(IntPtr aPtr, byte[] aData, int aBytes);
        public delegate void CallbackWriteResourceEnd(IntPtr aPtr);
        private unsafe delegate void CallbackResourceManager(IntPtr aUserData, char* aUriTail, uint aInterface, IntPtr aLanguageList, IntPtr aWriterData,
                                                             CallbackWriteResourceBegin aWriteBegin,
                                                             CallbackWriteResource aWriteResource,
                                                             CallbackWriteResourceEnd aWriteEnd);

        private IResourceManager iResourceManager;
        private CallbackResourceManager iCallbackResourceManager;

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        public unsafe DvDeviceStandard(string aUdn)
        {
            char* udn = (char*)Marshal.StringToHGlobalAnsi(aUdn).ToPointer();
            iHandle = DvDeviceStandardCreateNoResources(udn);
            Marshal.FreeHGlobal((IntPtr)udn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files</param>
        public unsafe DvDeviceStandard(string aUdn, IResourceManager aResourceManager)
        {
            iResourceManager = aResourceManager;
            iGch = GCHandle.Alloc(this);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            char* udn = (char*)Marshal.StringToHGlobalAnsi(aUdn).ToPointer();
            iCallbackResourceManager = new CallbackResourceManager(WriteResource);
            iHandle = DvDeviceStandardCreate(udn, iCallbackResourceManager, ptr);
            Marshal.FreeHGlobal((IntPtr)udn);
        }

        private static unsafe void WriteResource(IntPtr aUserData, char* aUriTail, uint aInterface, IntPtr aLanguageList, IntPtr aWriterData,
                                                 CallbackWriteResourceBegin aWriteBegin,
                                                 CallbackWriteResource aWriteResource,
                                                 CallbackWriteResourceEnd aWriteEnd)
        {
            GCHandle gch = GCHandle.FromIntPtr(aUserData);
            DvDeviceStandard self = (DvDeviceStandard)gch.Target;
            string uriTail = Marshal.PtrToStringAnsi((IntPtr)aUriTail);
            List<string> languageList = new List<string>();
            uint count = DvResourceWriterLanguageCount(aLanguageList);
            for (uint i = 0; i < count; i++)
            {
                languageList.Add(Marshal.PtrToStringAnsi(DvResourceWriterLanguage(aLanguageList, i)));
            }
            ResourceWriter writer = new ResourceWriter(aWriterData, aWriteBegin, aWriteResource, aWriteEnd);
            writer.Write(self.iResourceManager, uriTail, aInterface, languageList);
        }
    }
}
