rm *.so
rm QVRTTools.py
rm *.cxx
swig -c++ -python QVRTTools.i
c++ -c -fPIC -std=c++11 -I/usr/include/python3.5m/ QVRTTools_wrap.cxx # generate the QVRTTools_wrap.o file
c++ -shared QVRTTools_wrap.o circbuff.o qvrt_fileinfo.o qvrt_reader.o ExtDataRadioSettings.o qvrt_header.o qvrt_tool.o fixed_t.o qvrt_ifcontext_packet.o qvrt_writer.o qvrt_ext_context_packet.o qvrt_iqdatapacket.o qvrt_ext_data_packet.o qvrt_packet.o -I/usr/include/python3.5m/ -std=c++11 -fPIC -o _QVRTTools.so



#1. swig -python -c++ XXX.i
#2. c++ -c -fpic XXX.cpp (this command will generate XXX.o file)
#3. c++ -c -fpic XXX_wrap.cxx -I/usr/include/python2.7 (this command will generate XXX_wrap.o file)
#4. c++ -shared XXX.o XXX_wrap.o -o XXX.so
#circbuff.o qvrt_fileinfo.o qvrt_reader.o ExtDataRadioSettings.o qvrt_header.o qvrt_tool.o fixed_t.o qvrt_ifcontext_packet.o qvrt_writer.o qvrt_ext_context_packet.o qvrt_iqdatapacket.o qvrt_ext_data_packet.o qvrt_packet.o
