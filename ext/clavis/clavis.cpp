#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <httplib.h>

using namespace Rice;

class Clavis {
    public:
        Clavis();
        void clavis_run();
};

Clavis::Clavis() {}

void Clavis::clavis_run() {
    using namespace httplib;

    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.listen("localhost", 1234);
}

extern "C" {
    void Init_clavis() {
        Data_Type<Clavis> rb_cClavis = define_class<Clavis>("Clavis")
            .define_constructor(Constructor<Clavis>())
            .define_method("run", &Clavis::clavis_run);
    }
}