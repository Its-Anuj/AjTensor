/*
    Header Storing a Timer class meant to just see how long it takes to draw a proper conclusion of its efficiency.
*/

#include <chrono>

namespace Scratch
{
    class DebugTimer
    {
    public:
        DebugTimer(const char *Name)
            : _Name(Name)
        {
            _Start = std::chrono::high_resolution_clock::now();
        }

        ~DebugTimer()
        {
            _End = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(_End - _Start) ;
            PRINT(_Name << " took: " << duration.count() << " ms");
        }

    private:
        std::chrono::_V2::system_clock::time_point _Start, _End;
        std::string _Name;
    };
}

#if SCRATCH_DEBUG == SCRATCH_TRUE
#define SCRATCH_DEBUG_TIMER(Name) Scratch::DebugTimer _DebugTimer(Name);
#elif SCRATCH_DEBUG == SCRATCH_FALSE
#define SCRATCH_DEBUG_TIMER(Name) Scratch::DebugTimer _DebugTimer(Name);
#endif