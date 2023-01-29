/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class UsersService {

    /**
     * Username Available
     * @param username 
     * @returns any Successful Response
     * @throws ApiError
     */
    public static usernameAvailable(
username: string,
): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'GET',
            url: '/api/username-available',
            query: {
                'username': username,
            },
            errors: {
                422: `Validation Error`,
            },
        });
    }

}
