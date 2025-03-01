#include <qvrt_tools.h>
using namespace std;


int sum_it_cplx(long array, int size)
{
    /*
    std::complex<float> ret(0., 0.);
    for(int i=0; i<size; ++i) {
        ret += array[i];
    }
    */
    return size;
}

//int TestReadSamplesComplex(complex<float> *fcoutvec, int n)
int TestReadSamplesComplex(void *fcoutvec, int n)
{
    return n;
}

int TestReadSamples(double *outvec, int n)
{
    for(int c = 0; c < n; c++)
    {
        outvec[c] = 10;
    }
    return n;
}
void inplace(double *invec, int n)
{
    int i;

    for (i=0; i<n; i++)
    {
        invec[i] = 2*invec[i];
    }
}
/*  Compute the cosine of each element in in_array, storing the result in
 *  out_array. */
void cos_doubles(double * in_array, double * out_array, int size){
    int i;
    for(i=0;i<size;i++){
        out_array[i] = cos(in_array[i]);
    }
}

complex <float > * ALLOC_CF(int size)
{
    complex<float> * ptr = new complex<float>[size];
    return ptr;
}

void FREE_CF(complex<float> *ptr)
{
    delete []ptr;
}


std::string TSI2Name(int TSI)
{
    switch(TSI)
    {
        case TSI_NO_INT_TS: return "No integer timestamp";
        case TSI_COORD_UTC: return "Coordinate UTC Timestamp";
        case TSI_GPS: return "GPS Timestamp";
        case TSI_OTHER: return "Other";
    }
    return "unknown";
}

std::string TSF2Name(int TSF)
{
    switch(TSF)
    {
        case TSF_NO_FRAC_TS: return "No fractional timestamp";
        case TSF_SAMPLE_COUNT: return "sample count is used";
        case TSF_REAL_TIME: return "Real Time (picoseconds) timestamp";
        case TSF_FREE_RUNNING: return "free Running count";
    }
    return "unknown";
}

std::string PacketType2Name(int packettype)
{
    switch(packettype)
    {
        case QVRT_IQ_DATA_NO_STREAMID:  return "IQ_DATA_NO_STREAMID ";
        case QVRT_IQ_DATA:              return "IQ_DATA             ";
        case QVRT_EXT_DATA_NO_STREAMID: return "EXT_DATA_NO_STREAMID";
        case QVRT_EXT_DATA:             return "EXT_DATA            ";
        case QVRT_IF_CONTEXT:           return "IF_CONTEXT          ";
        case QVRT_EXT_CONTEXT:          return "EXT_CONTEXT         ";
    }
    return "unknown";
}

std::string hexStr(unsigned char* data, int len)
{
    std::stringstream ss;
    ss << std::hex;
    for(int i=0;i<len;++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
    return ss.str();
}


void DumpHexBlock(unsigned char *data,int size, int columns)
{
    if(data == nullptr)
        return;
    unsigned char *dptr = data;
    int col = 0;
    for(int c = 0 ; c < size ; c++)
    {
        printf("%02x ",*dptr);
        dptr++;
        col++;
        if(col == (columns))
        {
            printf("\r\n");
            col = 0;
        }
    }
}

std::string FileFormat2Str(file_format f)
{
    switch(f)
    {
        case eU8:
            return "2 channel unsigned 8 bit";
        case eS8:
            return "2 channel signed 8 bit";
        case eU16:
            return "2 channel unsigned 16 bit";
        case eS16:
            return "2 channel signed 16 bit";
        case e32:
            return "2 channel 32 bit float";
        case eQVRT:
            return "QVRT";
        case eUNK:
            return "Unknown file format";
    }
    return "Unknown file format";
}
