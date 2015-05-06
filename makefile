CXX := clang++
CXXFLAGS := -std=c++11 -Wall

soa-iterator: soa-iterator.cc
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: run
run: soa-iterator
	./$<

.PHONY: clean
clean:
	$(RM) soa-iterator
