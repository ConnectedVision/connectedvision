/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* RTPImporter_output_FrameMetadata.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "RTPImporter_output_FrameMetadata";
CREATE TABLE "RTPImporter_output_FrameMetadata"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) /* Object ID (string) */,
	'configID' VARCHAR(32) /* job / config ID (string) */,
	'timestamp' BIGINT /* frame time (integer) */,
	'framenumber' BIGINT NOT NULL DEFAULT '0' /* frame number (integer) */,
	'width' BIGINT NOT NULL DEFAULT '0' /* width of frame in pixels (integer) */,
	'height' BIGINT NOT NULL DEFAULT '0' /* height of frame in pixels (integer) */,
	'framediff' BIGINT /* difference between current framenumber and last (reflects dropped frames) (integer) */,
	'encerrors' BIGINT /* number of encoder errors (integer) */
);
