#include "litmus_tests.h"

namespace litmus {

Breath1::Breath1() : x_(0) {}
void Breath1::t1(Result& read) {
    x_.store(1, std::memory_order_relaxed);
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
}

Breath2::Breath2() : x_(0) {}
void Breath2::t1() {
    x_.store(1, std::memory_order_relaxed);
}
void Breath2::t2(Result& read) {
    while (!x_.load(std::memory_order_relaxed)){}
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
}

MPa::MPa() : x_(0), y_(0) {}
void MPa::t1() {
    x_.store(1, std::memory_order_relaxed);
    y_.store(1, std::memory_order_relaxed);
}
void MPa::t2(Result& read) {
    std::get<0>(read) = y_.load(std::memory_order_relaxed);
    std::get<1>(read) = x_.load(std::memory_order_relaxed);
}

MP::MP() : x_(0), y_(0) {}
void MP::t1() {
    x_.store(1, std::memory_order_relaxed);
    y_.store(1, std::memory_order_relaxed);
}
void MP::t2(Result& read) {
    while (!y_.load(std::memory_order_relaxed)){}
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
}


LB::LB() : x_(0), y_(0) {}
void LB::t1(Result& read) {
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
    y_.store(1, std::memory_order_relaxed);
}
void LB::t2(Result& read) {
    std::get<1>(read) = y_.load(std::memory_order_relaxed);
    x_.store(1, std::memory_order_relaxed);
}


SB::SB() : x_(0), y_(0) {}
void SB::t1(Result& read) {
    y_.store(1, std::memory_order_relaxed);
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
}
void SB::t2(Result& read) {
    x_.store(1, std::memory_order_relaxed);
    std::get<1>(read) = y_.load(std::memory_order_relaxed);
}

IRIW::IRIW() : x_(0), y_(0) {}
void IRIW::t1() {
    x_.store(1, std::memory_order_relaxed);
}

void IRIW::t2() {
    y_.store(1, std::memory_order_relaxed);
}

void IRIW::t3(Result& read) {
    std::get<0>(read) = x_.load(std::memory_order_relaxed);
    std::get<1>(read) = y_.load(std::memory_order_relaxed);
}

void IRIW::t4(Result& read) {
    std::get<2>(read) = y_.load(std::memory_order_relaxed);
    std::get<3>(read) = x_.load(std::memory_order_relaxed);
}


}  // close namespace litmus
