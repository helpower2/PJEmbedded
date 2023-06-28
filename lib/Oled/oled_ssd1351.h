/** OLED Display Driver for Hexiwear
 *  This file contains OLED driver functionality for drawing images and text
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 * Rewrite by Lorenzo Calisti, 2022
 */

#ifndef OLED_SSD1351_H_
#define OLED_SSD1351_H_

#include "mbed.h"
#include "oled_info.h"
#include "oled_types.h"

namespace oled
{
    class SSD1351
    {
    public:
        SSD1351(PinName mosiPin, PinName sclkPin,
                PinName pwrPin, PinName csPin,
                PinName rstPin, PinName dcPin);
        ~SSD1351();

        // Dim OLED screen on
        void dim_screen_on();

        // Return OLED back to full contrast
        void dim_screen_off();

        // Turn on Power for OLED Display
        void power_on();

        // Turn off Power for OLED Display
        void power_off();

        // Set OLED dynamic area
        Status set_dynamic_area(DynamicArea dynamic_area);

        // Fill the entire screen with specified color
        Status fill_screen(Color color);

        // Draw an image to OLED
        // Used with set_dynamic_area() for positioning it
        Status draw_image(const uint8_t *image);

        // Draw an image in the entire screen with a transition
        Status draw_screen(const uint8_t *image, Transition transition);

        // Draw a box on the OLED
        // Used with set_dynamic_area() for positioning it
        Status draw_box(Color color);

        // Draw a single pixel
        Status draw_pixel(uint8_t x, uint8_t y, Color color);

        // Create a text box; recommended for dynamic text.
        // Used with set_dynamic_area() for positioning the text box.
        Status text_box(const char *text);

        // Write text on the OLED at position x,y
        Status label(const char *text, uint8_t x, uint8_t y);

        // Set the OLED text properties
        void set_text_properties(TextProperties *prop);

        // Get the OLED text properties
        void get_text_properties(TextProperties *prop);

    private:
        // OLED device wires
        SPI _spi;
        DigitalOut _power;
        DigitalOut _cs;
        DigitalOut _rst;
        DigitalOut _dc;

        // Font related variables
        TextProperties _text_properties;
        uint16_t selectedFont_firstChar;
        uint16_t selectedFont_lastChar;
        uint16_t selectedFont_height;

        // Dynamic area
        DynamicArea _dynamic_area;
        pixel_t *_screen_buffer;
        pixel_t *_area_buffer;

        // Send a command to the OLED
        void send_cmd(Command cmd);

        // Send raw data to the OLED
        void send_data(const uint8_t *dataToSend, uint32_t dataSize);

        // Functions to manage the screen buffer
        void set_buffer_border(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
        void update_screen_buffer(pixel_t *image);
        void transpose_screen_buffer();
        void draw_screen_buffer();
        void draw_area_buffer();

        // Functions to draw screen with transition
        void draw_screen_top_down();
        void draw_screen_down_top();
        void draw_screen_left_right();
        void draw_screen_right_left();

        // Functions to draw text
        Status draw_text(const char *text);
        void compute_alignment(uint8_t lineWidth, uint8_t line_num, uint8_t lines, uint8_t *xOff, uint8_t *yOff);
        void write_char_to_buffer(pixel_t *buff, char charToWrite, uint8_t *xOffset, uint8_t *yOffset);
        int get_line_count(const char *text);
        uint8_t get_line_width(const char *text);
    };
} // namespace oled

#endif // OLED_SSD1351_H_