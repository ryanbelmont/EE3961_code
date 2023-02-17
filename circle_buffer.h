/* 
 * File:   circle_buffer.h
 * Author: ryan belmont
 * belmo057
 *
 * Created on November 17, 2021, 8:45 PM
 */

#ifndef CIRCLE_BUFFER_H
#define	CIRCLE_BUFFER_H

#include <xc.h>

#ifdef	__cplusplus 
extern "C" {
#endif

    void putVal(int newValue);
    int getAvg();
    void initBuffer();



#ifdef	__cplusplus
}
#endif

#endif	/* CIRCLE_BUFFER_H */

