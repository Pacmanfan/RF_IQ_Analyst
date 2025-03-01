#ifndef SDRKIT_H
#define SDRKIT_H

/*
This is a class to initialize the library in general, it may or may not be needed
in the future, I'm putting it in right now to do run-time detection of CUDA, because
we might have compiled with CUDA, but may not have a CUDA-compliant graphics card.
*/
class sdrkit
{
public:
    sdrkit();
    ~sdrkit();
    void Initialize();
    bool has_cuda{false};
};

#endif // SDRKIT_H
