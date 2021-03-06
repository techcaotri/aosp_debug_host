/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ASH_CAL_H_
#define ASH_CAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//! This is used to indicate the persistent storage of the ASH implementaion.
#define ASH_CAL_STORAGE_ASH UINT8_C(0)

//! This is used to indicate the persistent storage in the sensor registry.
#define ASH_CAL_STORAGE_SNS UINT8_C(1)

//! Interval between cal params storage when AP is up, in usec.
#define ASH_CAL_SAVE_INTERVAL_USEC UINT64_C(300000000)

//! This is used to indicate that the cal params are invalid.
#define ASH_CAL_PARAMS_SOURCE_NONE    UINT8_C(0)

//! This is used to indicate that the cal params were set by factory
//! calibration.
#define ASH_CAL_PARAMS_SOURCE_FACTORY UINT8_C(1)

//! This is used to indicate that the cal params were set by runtime
//! calibration.
#define ASH_CAL_PARAMS_SOURCE_RUNTIME UINT8_C(2)

/**
 * A struct for calibration parameters to be saved to and loaded from a
 * persistent area. The source of each section is indicated by the
 * corresponding *Source field, which is one of the ASH_CAL_PARAMS_SOURCE_*
 * constants.
 */
struct ashCalParams {
  //! The offset of the sensor in the x, y and z axis at temperature
  //! offsetTempCelsius.
  float offset[3];

  //! The temperature at which last offset was updated.
  float offsetTempCelsius;

  //! The temperature sensitivity of offset.
  float tempSensitivity[3];

  //! The estimated offset at zero degree Celsius.
  float tempIntercept[3];

  //! The scale factor of the x, y and z axis.
  float scaleFactor[3];

  //! The cross-axis factor in the [yx, zx, zy] order.
  float crossAxis[3];

  //! The source of offset[3]
  uint8_t offsetSource;

  //! The source of offsetTempCelsius
  uint8_t offsetTempCelsiusSource;

  //! The source of tempSensitivity[3]
  uint8_t tempSensitivitySource;

  //! The source of tempIntercept[3]
  uint8_t tempInterceptSource;

  uint8_t scaleFactorSource;

  //! The source of crossAxis[3]
  uint8_t crossAxisSource;
};

/**
 * Loads the stored cal params from the specified storage area.
 *
 * If ASH_CAL_STORAGE_SNS is specified as the storage area, it reads from the
 * sensor registry with factory cal params. This should only be used for
 * debugging as it can wake up the AP.
 *
 * If ASH_CAL_STORAGE_ASH is specified as the storage area, the stored cal
 * params in the ASH storage are provided if they exist. Otherwise, the sensor
 * registry cal params are provided instead.
 *
 * @param sensorType One of the CHRE_SENSOR_TYPE_* constants.
 * @param storage Either ASH_CAL_STORAGE_ASH or ASH_CAL_STORAGE_SNS.
 * @param params A non-null pointer to a ashCalParams that the cal params will
 *               be populated to.
 *
 * @return true if the cal params have been successfully populated to the
 *              provided memory.
 */
bool ashLoadCalibrationParams(uint8_t sensorType, uint8_t storage,
                              struct ashCalParams *params);

/**
 * Saves the cal params to a local cache, and saves to ASH's persistent storage
 * area when the AP wakes up, or when the AP is up and it has been
 * ASH_CAL_SAVE_INTERVAL_USEC since the cal params were last saved to the ASH
 * storage.
 *
 * @param sensorType One of the CHRE_SENSOR_TYPE_* constants.
 * @param params A non-null pointer to a ashCalParams to be saved to the local
 *               cache.
 *
 * @return true if the cal params have been successfully saved to the local
 *              cache.
 */
bool ashSaveCalibrationParams(uint8_t sensorType,
                              const struct ashCalParams *params);

#ifdef __cplusplus
}
#endif

#endif // ASH_CAL_H_
