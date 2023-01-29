/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class DevService {

    /**
     *  Get Users
     * @returns any Successful Response
     * @throws ApiError
     */
    public static getUsers(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'GET',
            url: '/dev/users',
        });
    }

}
