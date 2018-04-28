#include "interface/isl-noexceptions.h"

#include "assert.h"


void test_compute_out() {
    isl_ctx *ctx = isl_ctx_alloc();

    {
	fprintf(stderr, "\n\nReturn true on compute-out\n");
    	isl_ctx_set_max_operations(ctx, 1);
    	isl::set Universe(ctx, "{ [i] }");
    	bool ResTrue = Universe.is_empty(isl::quota::ret_true);
    	assert(ResTrue == true);
    }

    {
	fprintf(stderr, "\n\nReturn false on compute-out\n");
    	isl_ctx_set_max_operations(ctx, 1);
    	isl::set Empty(ctx, "{ [i] : false }");
    	bool ResFalse = Empty.is_empty(isl::quota::ret_false);
    	assert(ResFalse == false);
    }

    {
	fprintf(stderr, "\n\nReturn value on compute-out will be ignored\n");
    	isl_ctx_set_max_operations(ctx, 1);
    	isl::set Universe(ctx, "{ [i] }");
        bool ResIgnore = Universe.is_empty(isl::quota::ignore);
        assert(ResIgnore == true);
    }

    {
	fprintf(stderr, "\n\nCallbacks on compute out are not called\n");
    	isl_ctx_set_max_operations(ctx, 1);

 	int Count = 0;
    	isl::set Single(ctx, "{ [i] }");


	auto Increment = [&] (isl::basic_set bset) {
		Count++;
	};

        Single.foreach_basic_set(Increment);
	assert(Count == 0);
    }
}

int main(int argc, char **argv)
{
    test_compute_out();
    return 0;
}
