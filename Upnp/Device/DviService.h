#ifndef HEADER_DVISERVICE
#define HEADER_DVISERVICE

#include <OhNetTypes.h>
#include <Standard.h>
#include <Buffer.h>
#include <Thread.h>
#include <Service.h>
#include <Stream.h>
#include <FunctorDviInvocation.h>
#include <DviSubscription.h>
#include <Thread.h>
#include <Core/DvInvocationResponse.h>

#include <vector>

EXCEPTION(InvocationError);

namespace OpenHome {
namespace Net {

class IDviInvocation
{
public:
    virtual void Invoke() = 0;
    
    virtual void InvocationReadStart() = 0;
    virtual TBool InvocationReadBool(const TChar* aName) = 0;
    virtual void InvocationReadString(const TChar* aName, Brhz& aString) = 0;
    virtual TInt InvocationReadInt(const TChar* aName) = 0;
    virtual TUint InvocationReadUint(const TChar* aName) = 0;
    virtual void InvocationReadBinary(const TChar* aName, Brh& aData) = 0;
    virtual void InvocationReadEnd() = 0;

    virtual void InvocationReportError(TUint aCode, const Brx& aDescription) = 0;

    virtual void InvocationWriteStart() = 0;
    virtual void InvocationWriteBool(const TChar* aName, TBool aValue) = 0;
    virtual void InvocationWriteInt(const TChar* aName, TInt aValue) = 0;
    virtual void InvocationWriteUint(const TChar* aName, TUint aValue) = 0;
    virtual void InvocationWriteBinaryStart(const TChar* aName) = 0;
    virtual void InvocationWriteBinary(TByte aValue) = 0;
    virtual void InvocationWriteBinary(const Brx& aValue) = 0;
    virtual void InvocationWriteBinaryEnd(const TChar* aName) = 0;
    virtual void InvocationWriteStringStart(const TChar* aName) = 0;
    virtual void InvocationWriteString(TByte aValue) = 0;
    virtual void InvocationWriteString(const Brx& aValue) = 0;
    virtual void InvocationWriteStringEnd(const TChar* aName) = 0;
    virtual void InvocationWriteEnd() = 0;

    virtual ~IDviInvocation() {}
};

class DvAction
{
public:
    DvAction(OpenHome::Net::Action* aAction, FunctorDviInvocation aFunctor);
    OpenHome::Net::Action* Action();
    const OpenHome::Net::Action* Action() const;
    FunctorDviInvocation Functor() const;
private:
    OpenHome::Net::Action* iAction;
    FunctorDviInvocation iFunctor;
};

class DviDevice;
class DviService : public Service
{
public:
    DviService(const TChar* aDomain, const TChar* aName, TUint aVersion);
    void AddRef();
    void RemoveRef();

    DllExport void AddAction(Action* aAction, FunctorDviInvocation aFunctor);
    typedef std::vector<DvAction> VectorActions;
    const VectorActions& DvActions() const;
    void Invoke(IDviInvocation& aInvocation, TUint aVersion, const Brx& aActionName);

    void PropertiesLock();
    void PropertiesUnlock();
    DllExport void AddProperty(Property* aProperty);
    typedef std::vector<Property*> VectorProperties;
    const VectorProperties& Properties() const;
    void PublishPropertyUpdates();

    void AddSubscription(DviSubscription* aSubscription);
    void RemoveSubscription(const Brx& aSid);
private:
    ~DviService();
private:
    Mutex iLock;
    TUint iRefCount;
    Mutex iPropertiesLock;
    VectorActions iDvActions;
    VectorProperties iProperties;
    std::vector<DviSubscription*> iSubscriptions;
};

class DllExportClass InvocationResponse : public IInvocationResponse, private INonCopyable
{
public:
	DllExport InvocationResponse(IDviInvocation& aInvocation);
	virtual void Error(TInt aCode, const Brx& aReason);
	virtual void Start();
	virtual void End();
private:
	IDviInvocation& iInvocation;
};

class DllExportClass InvocationResponseBool : public IInvocationResponseBool, private INonCopyable
{
public:
	DllExport InvocationResponseBool(IDviInvocation& aInvocation, const TChar* aName);
	void Write(TBool aValue);
private:
	IDviInvocation& iInvocation;
	const TChar* iName;
};

class DllExportClass InvocationResponseUint : public IInvocationResponseUint, private INonCopyable
{
public:
	DllExport InvocationResponseUint(IDviInvocation& aInvocation, const TChar* aName);
	void Write(TUint aValue);
private:
	IDviInvocation& iInvocation;
	const TChar* iName;
};

class DllExportClass InvocationResponseInt : public IInvocationResponseInt, private INonCopyable
{
public:
	DllExport InvocationResponseInt(IDviInvocation& aInvocation, const TChar* aName);
	void Write(TInt aValue);
private:
	IDviInvocation& iInvocation;
	const TChar* iName;
};

class DllExportClass InvocationResponseBinary : public IInvocationResponseBinary, private INonCopyable
{
public:
	DllExport InvocationResponseBinary(IDviInvocation& aInvocation, const TChar* aName);
	// IWriter
    void Write(TByte aValue);
    void Write(const Brx& aValue);
    void WriteFlush();
private:
	void CheckFirst();
private:
	IDviInvocation& iInvocation;
	const TChar* iName;
	TBool iFirst;
};

class DllExportClass InvocationResponseString : public IInvocationResponseString, private INonCopyable
{
public:
	DllExport InvocationResponseString(IDviInvocation& aInvocation, const TChar* aName);
	// IWriter
    void Write(TByte aValue);
    void Write(const Brx& aValue);
    void WriteFlush();
private:
	void CheckFirst();
private:
	IDviInvocation& iInvocation;
	const TChar* iName;
	TBool iFirst;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVISERVICE
