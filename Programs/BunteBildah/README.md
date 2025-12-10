
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

semantics
- [ ] just based on names, shouldn't the line be saved in the line module?
- [ ] just based on names, get_color() should return the color no matter
        if we use a palette or not. maybe we should combine palette and
        color into one module?