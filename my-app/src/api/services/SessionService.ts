/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { Body_login } from '../models/Body_login';
import type { Body_register } from '../models/Body_register';

import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class SessionService {

    /**
     * Register
     * @param formData 
     * @returns any Successful Response
     * @throws ApiError
     */
    public static register(
formData: Body_register,
): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/register',
            formData: formData,
            mediaType: 'application/x-www-form-urlencoded',
            errors: {
                422: `Validation Error`,
            },
        });
    }

    /**
     * Login
     * @param formData 
     * @returns any Successful Response
     * @throws ApiError
     */
    public static login(
formData: Body_login,
): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/login',
            formData: formData,
            mediaType: 'application/x-www-form-urlencoded',
            errors: {
                422: `Validation Error`,
            },
        });
    }

    /**
     * Logout
     * @returns any Successful Response
     * @throws ApiError
     */
    public static logout(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/logout',
        });
    }

    /**
     * Logout All
     * @returns any Successful Response
     * @throws ApiError
     */
    public static logoutAll(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/logout-all',
        });
    }

}
