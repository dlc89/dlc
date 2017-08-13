#include "MyFirstPlugin.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"
#include <math.h>

#include <algorithm>
const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 27,
  kGainY = 62,
  kKnobFrames = 128
};

MyFirstPlugin::MyFirstPlugin(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 0.0, 0., 100.0, 0.01, "%","Group");//Iparam class starts the chain 
  //InitDouble is an Iparam class method and GetParam is from Iplugbase.h with an Iparam class that has a Iplugbase::getparampointer 
  GetParam(kGain)->SetShape(1.0); // all so far is called functions lol


  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight); // setting pointer for later AttachGraphics(pGraphics);
  pGraphics->AttachBackground(BLACKJA_ID, BLACKJA_FN);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));
  /*pGraphics->AttachControl(new IKnobMultiControl(this, 300, 90, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, 600, 80, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, 430, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, 300, 430, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, 600, 430, kGain, &knob));
*/

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms); // all called functions
}

MyFirstPlugin::~MyFirstPlugin() {}

void MyFirstPlugin::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)   // this is defining hah lol 

{
  // Mutex is already locked for us.

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  //double mPhase =0 ; double mPhaseIncrement = 0 ;
  //const double mPI= 0;
  //const double twoPI = 2 * mPI;


  for (int s = 0; s < nFrames;s++,out1++)
  {


  out1[s]= sin(.66) * mGain ;
  // *out1 and out1[s]


   //out2[s]=out1[s];
  
  // mPhase += mPhaseIncrement;
    //            while (mPhase >= twoPI) {
		//			mPhase -= twoPI;}
}
  
}
 // Copy left buffer into right buffer:
  
/*
int delayMilliseconds = 500; // half a second
int delaySamples = 
    (int)((float)delayMilliseconds * 44.1f); // assumes 44100 Hz sample rate
float decay = 0.5f;
for (int i = 0; i < buffer.length - delaySamples; i++)
{
    // WARNING: overflow potential
    buffer[i + delaySamples] += (short)((float)buffer[i] * decay);
} 
*/



void MyFirstPlugin::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void MyFirstPlugin::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}
