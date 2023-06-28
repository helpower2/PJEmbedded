#include "mbed.h"

/**
 * A class for handling debounced button presses.
 */
class DebouncedButton {
public:
    /**
     * Constructor for DebouncedButton.
     * @param pin The pin to use for the button.
     * @param pressed The callback to call when the button is pressed.
     * @param mode The pin mode to use (default: PullUp).
     * @param debounceTime The debounce time to use (default: 100ms).
     * @param timer The timer to use (default: LowPowerTimer).
     */
    DebouncedButton(PinName pin, Callback<void()> pressed, PinMode mode = PinMode::PullUp,
                    chrono::duration<int64_t, milli> debounceTime = 100ms,const TimerBase& timer = LowPowerTimer())
            : _button(pin, mode), _pressed(pressed), _debounceTime(debounceTime), _timer(const_cast<TimerBase &>(timer))
    {
        _button.fall(callback(this, &DebouncedButton::handleFall));
        _timer.start();
    }
    ~DebouncedButton(){};
    /**
     * Changes the debounce time for the button.
     * @param debounceTime The new debounce time to use.
     */
    void setDebounceTime(chrono::duration<int64_t, milli> debounceTime) {
        _debounceTime = debounceTime;
    }

private:
    InterruptIn _button;
    Callback<void()> _pressed;
    chrono::duration<int64_t, milli> _debounceTime;
    TimerBase& _timer;

    /**
     * Handles the falling edge interrupt for the button.
     */
    void handleFall() {
        if (_timer.elapsed_time() > _debounceTime) {
            if (_pressed) _pressed.call();
            _timer.reset();
        }
    }

};