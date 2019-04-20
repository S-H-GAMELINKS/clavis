#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace Rice;

class Clavis {
    public:
        Clavis();
};

Clavis::Clavis() {}

extern "C" {
    void Init_clavis() {
        Data_Type<Clavis> rb_cClavis = define_class<Clavis>("Clavis")
            .define_constructor(Constructor<Clavis>());
    }
}