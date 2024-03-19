/*
 * DriveUnitDefineStructs.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Windows
 */

#ifndef DRIVEUNITDEFINESTRUCTS_H_
#define DRIVEUNITDEFINESTRUCTS_H_

#include "fx_api.h"


typedef struct fileDataUSB
{
    FX_FILE *p_file;
    ULONG   file_pos;
    INT     file_open;
}fileDataUSB;
//
//  **Retains information about the properties and state of the USB
//
#define USB_FILE_MAX_COUNT      10
#define USB_MEDIA_VOLUME_SIZE   32

struct machineGlobalsUSB
{
    CHAR USBPlugIn;
    UINT USB_media_open;
    FX_MEDIA * p_media;
    CHAR volume[USB_MEDIA_VOLUME_SIZE];
//    FX_FILE my_file;
    fileDataUSB file_data[USB_FILE_MAX_COUNT];
};




#endif /* DRIVEUNITDEFINESTRUCTS_H_ */
