/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* generic_status.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "generic_status";
CREATE TABLE "generic_status"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* config id (string) */,
	'timestamp' BIGINT /* time of modification (integer) */,
	'moduleID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of module (string) */,
	'moduleURI' TEXT NOT NULL DEFAULT '' /* URI of module instance (string) */,
	'commandQueue._idx1' BIGINT /* array index dimension: 1 (array) */,
	'commandQueue' TEXT /*  (string) */,
	'status' TEXT NOT NULL DEFAULT 'n/a' /* current status of config / job (string) */,
	'message' TEXT /* general message (e.g. description of last error) (string) */,
	'progress' DOUBLE NOT NULL DEFAULT '0' /* processing progress (0.0 - 1.0) (number) */,
	'startTime' BIGINT NOT NULL DEFAULT '-1' /* System time when the config was started. (integer) */,
	'systemTimeProcessing' BIGINT NOT NULL DEFAULT '-1' /* System time when the config was / is processed. This time is updated only during processing the config (i.e. status='running'). (integer) */,
	'estimatedFinishTime' BIGINT DEFAULT '-1' /* estimated time to finish processing of this configChain (integer) */,
	'qualityOfService.compuationDuration' BIGINT DEFAULT '-1' /* computation duration based on the elapsed time between updates of the systemTimeProcessing parameter (integer) */,
	'qualityOfService.compuationDurationAverage' BIGINT DEFAULT '-1' /* average of the computation duration of 10 preceding iterations based on the elapsed time between updates of the systemTimeProcessing parameter computed using the simple moving average method (integer) */,
	'stableResults._idx1' BIGINT /* array index dimension: 1 (array) */,
	'stableResults.pinID' TEXT /* id of output pin (string) */,
	'stableResults.indexStart' BIGINT /*  (integer) */,
	'stableResults.indexEnd' BIGINT /*  (integer) */,
	'stableResults.timestampStart' BIGINT /*  (integer) */,
	'stableResults.timestampEnd' BIGINT /*  (integer) */,
	'chain._idx1' BIGINT /* array index dimension: 1 (array) */,
	'chain' BLOB /*  (any) */,
	'configID' VARCHAR(32) /* virtual config id (string) */
);
