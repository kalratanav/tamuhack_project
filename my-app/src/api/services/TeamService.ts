/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { CancelablePromise } from '../core/CancelablePromise';
import { OpenAPI } from '../core/OpenAPI';
import { request as __request } from '../core/request';

export class TeamService {

    /**
     * Get Teams
     * @returns any Successful Response
     * @throws ApiError
     */
    public static getTeams(): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'GET',
            url: '/api/teams',
        });
    }

}
