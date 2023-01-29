/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
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

}
