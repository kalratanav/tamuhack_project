/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { Body_upload_floors_csv } from '../models/Body_upload_floors_csv';

import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class FloorService {

    /**
     * Get Floors
     * @returns any Successful Response
     * @throws ApiError
     */
    public static getFloors(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'GET',
            url: '/api/floors',
        });
    }

    /**
     * Upload Floors Csv
     * @param formData 
     * @returns any Successful Response
     * @throws ApiError
     */
    public static uploadFloorsCsv(
formData: Body_upload_floors_csv,
): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/floors/upload',
            formData: formData,
            mediaType: 'multipart/form-data',
            errors: {
                422: `Validation Error`,
            },
        });
    }

}
