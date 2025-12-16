
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

TO-DO:
- [ ] adjust line array length to be max. 5 times the LCD_WIDTH, like needed for assignment c.
- [ ] error when needed compression ratio is too large
- [ ] error when picture signature is borked
- [ ] handle error in get_next_line.
- [ ] comment and rename

functionality
- [ ] reader.c: überarbeite das RLE8 compressed line gedöns
- [ ] reader / line skip to next Line und eof checken 
- [ ] how to proceed with new height? (or new picture size in general)
- [ ] how does the delta work? is it implemented correctly in line.c
            especially line 194+/- in line.c
- [ ] at some point save pixel_color because it will always be WHITE otherwise!
- [ ] should not draw "BildSignaturDefekt.bmp"

semantics
- [ ] just based on names, shouldn't the line be saved in the line module?
- [ ] just based on names, get_color() should return the color no matter
        if we use a palette or not. maybe we should combine palette and
        color into one module?

---

working:
- uncompressed images (8-Bit and 24-Bit)
- very small images
- the smaller image versions of the two cars, the its board, and the blue boxes

not working:
- pretty much everything else
- compressed images are still drawn upside down

notes:
- partially working images and the blue ones with red border (580x400 & 1440_1280) are probably good for testing next! 

---

working images:
- 22x14_8_bit_komprimiert_sehr_kleines_testbild.bmp
- 2400_1600_pixel_some_colors_8_bit_compressed.bmp
- 400_260_pixel_red_frame_1_pixel_8_bit_compressed.bmp
- 400_260_pixel_red_frame_2_pixel_8_bit_compressed.bmp
- 400_260_pixel_red_frame_5_pixel_8_bit_compressed.bmp
- 400_260_pixel_some_colors_8_bit_compressed.bmp
- 479_320_pixel_RECBAR_8_bit_compressed.bmp
- 480_270_pixel_SecVI_8_bit_compressed.bmp
- 480_320_pixel_ITSboard_8_bit_compressed.bmp
- 480_320_pixel_red_frame_1_pixel_8_bit_compressed.bmp
- 480_320_pixel_red_frame_2_pixel_8_bit_compressed.bmp
- 480_320_pixel_red_frame_5_pixel_8_bit_compressed.bmp
- 480_320_pixel_some_colors_8_bit_compressed.bmp
- 580_400_pixel_some_colors_8_bit_compressed.bmp
- 60x50_8_bit_komprimiert_kleines_testbild.bmp
- 640x480_24_bit_nicht_komprimiert_ohne_padding_bytes_blauer_rahmen.bmp
- 6x10_8_bit_nicht_komprimiert_mit_padding_bytes.bmp
- 480_320_pixel_red_frame_1_pixel_8_bit_uncompressed.bmp

partially correct (fonts & colored cubes):
- 128x480_8_bit_komprimiert_zeile_zu_lang.bmp
- 640x480_8_bit_komprimiert_amrandrle.bmp
- 640x480_8_bit_komprimiert_einfaches_testbild.bmp (but mostly correct!)
- 640x480_8_bit_komprimiert_mehr_farben.bmp (but mostly correct!)
- 640x480_8_bit_komprimiert_rechtecke_am_bildrand.bmp
- 640x480_IM_HEADER_biWidth_viel_zu_goss_8_bit_komprimiert.bmp
- 640x480_IM_HEADER_biWidth_zu_goss_8_bit_komprimiert.bmp

weird border (blue square with red border around):
- 1440_1280_pixel_red_frame_1_pixel_8_bit_compressed.bmp
- 1440_1280_pixel_red_frame_2_pixel_8_bit_compressed.bmp
- 1440_1280_pixel_red_frame_5_pixel_8_bit_compressed.bmp
- 2400_1600_pixel_red_frame_1_pixel_8_bit_compressed.bmp
- 2400_1600_pixel_red_frame_2_pixel_8_bit_compressed.bmp
- 2400_1600_pixel_red_frame_5_pixel_8_bit_compressed.bmp
- 580_400_pixel_red_frame_1_pixel_8_bit_compressed.bmp
- 580_400_pixel_red_frame_2_pixel_8_bit_compressed.bmp
- 580_400_pixel_red_frame_5_pixel_8_bit_compressed.bmp

completely jumbled and/or stopping early:
- 1280_854_pixel_RECBAR_8_bit_compressed.bmp
- 1440_1280_pixel_some_colors_8_bit_compressed.bmp
- 4488_2525_pixel_SecVI_8_bit_compressed.bmp
- 6000_4000_pixel_ITSboard_8_bit_compressed.bmp
- 720_400_8_bit_komprimiert.bmp

completely jumbled:
- BildSignaturDefekt.bmp (this one shouldn't even draw at all)
