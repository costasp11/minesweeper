//
// Created by Costas on 4/21/24.
//
using namespace std;
// includes time header
#include <chrono>
#include <iostream>


#ifndef MINESWEEPER_CLOCK_H
#define MINESWEEPER_CLOCK_H


class Clock {
    private:
        // creates a start point on this point in time.
        chrono::steady_clock::time_point startTime;
        chrono::steady_clock::duration pausedDuration;
        bool isPaused;

    public:
        Clock() {
            isPaused = false;
        }

        void start() {
            startTime = chrono::steady_clock::now();
            // duration counts during a certain period (when time is paused)
            pausedDuration = chrono::steady_clock::duration::zero();
            isPaused = false;
        }

        void pause() {
            if (!isPaused) {
                pausedDuration += chrono::steady_clock::now() - startTime;
                isPaused = true;
            }
        }

        void resume() {
            if (isPaused) {
                startTime = chrono::steady_clock::now();
                isPaused = false;
            }
        }

        chrono::steady_clock::duration elapsed() const {
            if (isPaused) {
                return pausedDuration;
            } else {
                return chrono::steady_clock::now() - startTime + pausedDuration;
            }
        }

        void restart() {
            start();
        }
    };



#endif //MINESWEEPER_CLOCK_H
