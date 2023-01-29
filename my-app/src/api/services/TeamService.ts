/* istanbul ignore file */
/* tslint:disable */
/* eslint-disable */
import type { Body_upload_teams_csv } from '../models/Body_upload_teams_csv';

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

    /**
     * Upload Teams Csv
     * @param formData 
     * @returns any Successful Response
     * @throws ApiError
     */
    public static uploadTeamsCsv(
formData: Body_upload_teams_csv,
): CancelablePromise<any> {
        return __request(OpenAPI, {
            method: 'POST',
            url: '/api/teams/upload',
            formData: formData,
            mediaType: 'multipart/form-data',
            errors: {
                422: `Validation Error`,
            },
        });
    }

}
