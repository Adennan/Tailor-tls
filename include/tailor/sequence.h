#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

namespace tailor {
    class Sequence {
    private:
        uint64_t seq;

    public:
        uint64_t& getSeq() { return this->seq; }

        Sequence CreateSequence(uint64_t start)
        {
            Sequence seq;
            if (start == 0)
            {
                start = 1;
            }
            seq.seq = start;
            return seq
        }
        
        uint64_t current(Sequence seq)
        {
            return seq.seq;
        }
        
        void increase(Sequence seq)
        {
            seq.seq = (seq.seq + 1) & 0xffffffff;
        }
    };
}

#endif // SEQUENCE_H