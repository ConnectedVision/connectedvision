/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* VideoImporter_output_FrameMetadata.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "VideoImporter_output_FrameMetadata";
CREATE TABLE "VideoImporter_output_FrameMetadata"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) /* Object ID (string) */,
	'configID' VARCHAR(32) /* job / config ID (string) */,
	'timestamp' BIGINT /* frame time (integer) */,
	'framenumber' BIGINT NOT NULL DEFAULT '0' /* frame number (integer) */,
	'width' BIGINT NOT NULL DEFAULT '0' /* width of frame in pixels (integer) */,
	'height' BIGINT NOT NULL DEFAULT '0' /* height of frame in pixels (integer) */
);
