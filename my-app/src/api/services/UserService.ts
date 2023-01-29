/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class UserService {

    /**
     * Get User
     * @returns any Successful Response
     * @throws ApiError
     */
    public static getUser(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'GET',
            url: '/api/user',
        });
    }

    /**
     * Calculate
     * @returns any Successful Response
     * @throws ApiError
     */
    public static calculate(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/calculate',
        });
    }

}
