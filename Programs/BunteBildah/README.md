
Templates

/**
* @file       
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      
*/


/**
* @brief      -
*
* @param      -
* 
* @return     -
*/

~ ~ ~ ~ ~  T O  -  D O   ~ ~ ~ ~ ~

functionality
- [ ] reader.c: überarbeite das RLE8 compressed line gedöns
- [ ] reader / line skip to next Line und eof checken 
- [ ] how to proceed with new height? (or new picture size in general)
- [ ] how does the delta work? is it implemented correctly in line.c
            especially line 194+/- in line.c
- [ ] at some point save pixel_color because it will always be WHITE otherwise!

semantics
- [ ] just based on names, shouldn't the line be saved in the line module?
- [ ] just based on names, get_color() should return the color no matter
        if we use a palette or not. maybe we should combine palette and
        color into one module?

working:
- uncompressed images (8-Bit and 24-Bit)

not working:
- 


testing images that fit on screen:

        working
22x14_8_bit_komprimiert_sehr_kleines_testbild.bmp
400_260_pixel_red_frame_1_pixel_8_bit_compressed.bmp
400_260_pixel_red_frame_2_pixel_8_bit_compressed.bmp
400_260_pixel_red_frame_5_pixel_8_bit_compressed.bmp
480_320_pixel_red_frame_1_pixel_8_bit_compressed.bmp
480_320_pixel_red_frame_2_pixel_8_bit_compressed.bmp
480_320_pixel_red_frame_5_pixel_8_bit_compressed.bmp
60x50_8_bit_komprimiert_kleines_testbild.bmp
6x10_8_bit_nicht_komprimiert_mit_padding_bytes.bmp
480_320_pixel_red_frame_1_pixel_8_bit_uncompressed.bmp

        working, but upside down (might be same for others but can't tell because symmetrical)
400_260_pixel_some_colors_8_bit_compressed.bmp
480_320_pixel_some_colors_8_bit_compressed.bmp
        not working

128x480_8_bit_komprimiert_zeile_zu_lang.bmp
479_320_pixel_RECBAR_8_bit_compressed.bmp
480_270_pixel_SecVI_8_bit_compressed.bmp
480_320_pixel_ITSboard_8_bit_compressed.bmp