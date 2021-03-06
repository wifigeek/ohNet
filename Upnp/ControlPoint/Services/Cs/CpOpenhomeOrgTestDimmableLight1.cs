using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgTestDimmableLight1 : ICpProxy, IDisposable
    {
        void SyncGetLevel(out uint aLevel);
        void BeginGetLevel(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLevel(IntPtr aAsyncHandle, out uint aLevel);
        void SyncSetLevel(uint aLevel);
        void BeginSetLevel(uint aLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLevel(IntPtr aAsyncHandle);
        void SetPropertyA_ARG_LevelChanged(System.Action aA_ARG_LevelChanged);
        uint PropertyA_ARG_Level();
    }

    internal class SyncGetLevelOpenhomeOrgTestDimmableLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestDimmableLight1 iService;
        private uint iLevel;

        public SyncGetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1 aProxy)
        {
            iService = aProxy;
        }
        public uint Level()
        {
            return iLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLevel(aAsyncHandle, out iLevel);
        }
    };

    internal class SyncSetLevelOpenhomeOrgTestDimmableLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestDimmableLight1 iService;

        public SyncSetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetLevel(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the openhome.org:TestDimmableLight:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgTestDimmableLight1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgTestDimmableLight1
    {
        private OpenHome.Net.Core.Action iActionGetLevel;
        private OpenHome.Net.Core.Action iActionSetLevel;
        private PropertyUint iA_ARG_Level;
        private System.Action iA_ARG_LevelChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgTestDimmableLight1(CpDevice aDevice)
            : base("openhome-org", "TestDimmableLight", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            

            iActionGetLevel = new OpenHome.Net.Core.Action("GetLevel");
            param = new ParameterUint("Level");
            iActionGetLevel.AddOutputParameter(param);

            iActionSetLevel = new OpenHome.Net.Core.Action("SetLevel");
            param = new ParameterUint("Level");
            iActionSetLevel.AddInputParameter(param);

            iA_ARG_Level = new PropertyUint("A_ARG_Level", A_ARG_LevelPropertyChanged);
            AddProperty(iA_ARG_Level);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aLevel"></param>
        public void SyncGetLevel(out uint aLevel)
        {
            SyncGetLevelOpenhomeOrgTestDimmableLight1 sync = new SyncGetLevelOpenhomeOrgTestDimmableLight1(this);
            BeginGetLevel(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aLevel = sync.Level();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLevel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLevel(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLevel, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLevel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aLevel"></param>
        public void EndGetLevel(IntPtr aAsyncHandle, out uint aLevel)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aLevel"></param>
        public void SyncSetLevel(uint aLevel)
        {
            SyncSetLevelOpenhomeOrgTestDimmableLight1 sync = new SyncSetLevelOpenhomeOrgTestDimmableLight1(this);
            BeginSetLevel(aLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLevel().</remarks>
        /// <param name="aLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetLevel(uint aLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetLevel.InputParameter(inIndex++), aLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetLevel(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Set a delegate to be run when the A_ARG_Level state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestDimmableLight1 instance will not overlap.</remarks>
        /// <param name="aA_ARG_LevelChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyA_ARG_LevelChanged(System.Action aA_ARG_LevelChanged)
        {
            lock (iPropertyLock)
            {
                iA_ARG_LevelChanged = aA_ARG_LevelChanged;
            }
        }

        private void A_ARG_LevelPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iA_ARG_LevelChanged);
            }
        }

        /// <summary>
        /// Query the value of the A_ARG_Level property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the A_ARG_Level property</returns>
        public uint PropertyA_ARG_Level()
        {
            PropertyReadLock();
            uint val = iA_ARG_Level.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyOpenhomeOrgTestDimmableLight1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionGetLevel.Dispose();
                iActionSetLevel.Dispose();
                iA_ARG_Level.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

