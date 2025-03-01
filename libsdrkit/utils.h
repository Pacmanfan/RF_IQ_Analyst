#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <qvrt_tools.h>
// Some various settings for system  defaults

#define DEFAULT_NUM_BINS_FFT 4096
#define DEFAULT_SIGNAL_DETECTOR_UPDATE_RATE_HZ 10
#define DEFAULT_PEAK_DETECTOR_UPDATE_RATE_HZ 10
#define DEFAULT_FFT_UPDATE_RATE_HZ 20
#define RBW_MIN 1500 // minumum bandwidth resolution before we have to start using zoomfft
#define MAX_NB_SIG_WIDTH 25000 // maximum width of the narrowband signal
#define SIG_WIDTH_SCALER 15.0
#define SAMPLE_DURATION_SECONDS 3 // duration of the DDC'd sample to extract
#define MIN_SIGNAL_WIDTH 4000 // a signal must be at least this wide to be considered
#define MOCK_HOST 1 // use a dummy host for testing


#define PLAYMAKER_COMPONENT 0


file_format DetermineFormat(QString filename);

#endif // UTILS_H
