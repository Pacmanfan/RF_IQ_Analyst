#ifndef IPLUGININTERFACE_H
#define IPLUGININTERFACE_H

#include <QObject>
#define PROCESS_SIZE 10000 // size of the chunks of data that we process in a pass

#define PLG_FLAG_STREAM    0x01 // supports the 'Process' method
#define PLG_FLAG_TOOL      0x02 // supports the longer running 'Tool' method

/*
This is the base class for the plugins used by the Analyst project
The goal is to support a rich set of decoders and demodulators
that can decode and analyze a variety of signal types

I want plugins to be able to define GUIs
 both widgets and windows

We're going to run into the issue of how to define data in and out
 for now, we're going to use void pointers for a single
 in and output stream

 we need a way to define and retrieve that I/O parameter list for the process function
    (at compile time? / run time?)

     possible in / out types
     enumerated types?
     list of in/out data types?

We should pass data via UDP
this will allow multiple plugins to process data
it will also allow easier intgegration of plugins that run in separate processes
that are wrapped by this iplugininterface

*/
enum StreamItem
{
    eComplex, // 2 x 32bit float
    eFloat, // 32bit float
    eInt, // 32bit int
    eShort, // 16 bit
    eByte // can be used for strings as well
};

extern char StreamItemStrings[5][11];

// signature for an input / output stream
struct StreamSig
{
    StreamItem _itemtype; // the data type in this stream  
};

struct ProcessSignature
{
    int numin; // number of input streams
    int numout; // number of output streams

    StreamSig *insigs; // array of signatures that describe the input streams
    StreamSig *outsigs; // array of signatures that describe the outout streams
};

/*
Some plugins are simple stream processors,
The calling application like Analyst or Commander can open up a UDP port and send data
and get the decoded response
This allows for things such as simple AM/FM/QAM/P25/DMR decoders

Other plugins act more as general tools, such as the energy detector
These types of plugins can have a longer running process on an independant thread

These plugins should also be able to access an application singleton object to retrieve
things like the FFT_HIst, marker set, FFT Builder, SampleIndex amd other objects
For these longer running tools, a start and stop function should be provided
Some sort of signalling mechanism should also be used.
Yet other plugins are wrapped by a plugins class. These app can launch thier own processes and commincate soley through UDP/TCP/IP or other IPIC and ahave a
wrapped re-postioned GUI.

*/
// this should declare pure virtual functions only
class iPluginInterface
{
public:
    virtual ~iPluginInterface(){}
    virtual QString Name() = 0; // get the name of the plugin
    virtual QString Version() = 0; // get version number - should be "W.X.Y.Z" format
    virtual QString Description() = 0; // get a brief description
    virtual QString Tags() = 0; // CSV list of tags

    virtual QWidget *GetConfigGUI() = 0; // get the configuration GUI (optional - can return null)
    virtual QWidget *GetDisplayGUI() = 0; // a more full-fledged GUI for displaying live data (optional - can return null) - can also be a widget wrapping an external process

    // for stream processing:
    virtual ProcessSignature Signature() = 0; // the I/O signature
  //  virtual long Process(plg_vector_const_void_star &datain, plg_vector_void_star &dataout, int num_in) = 0; // getting rid of this
    virtual bool SetInputRate(double rate) = 0; // if applicable
    virtual bool SetOutputRate(double rate) = 0; // if applicable
    virtual double GetInputRate()=0; // returns the input rate or -1 if not applicable
    virtual double GetOutputRate()=0; // returns the output rate or -1 if not applicable
    // UDP communication ports - all ports should be open as shared
    virtual bool SetInPort(int udp_port,int idx=0) = 0; //
    virtual bool SetOutPort(int udp_port,int idx=0) = 0;
    virtual bool SetControlPort(int udp_port) = 0;
    virtual int GetInPort(int idx=0) = 0; //
    virtual int GetOutPort(int idx=0) = 0;
    virtual int GetControlPort() = 0;

    // for longer running tools:
    virtual bool Start()=0;
    virtual bool Stop()=0;
    virtual bool IsRunning()=0;
    //reporting the types:
    virtual unsigned int Flags()=0;
};

//define a string for the interface
#define iPluginInterface_iid "QRC.Analyst.iPluginInterface"
//declare this class uses that interface
Q_DECLARE_INTERFACE(iPluginInterface, iPluginInterface_iid)

#endif // IPLUGININTERFACE_H
