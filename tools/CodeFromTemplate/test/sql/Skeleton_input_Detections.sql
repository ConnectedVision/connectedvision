/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* Skeleton_input_Detections.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "Skeleton_input_Detections";
CREATE TABLE "Skeleton_input_Detections"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'objectID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* first detection (integer) */,
	'boundingBox.left' DOUBLE /* x position of top left point of the rectangle (number) */,
	'boundingBox.right' DOUBLE /* x position of bottom right point of the rectangle (number) */,
	'boundingBox.top' DOUBLE /* y position of top left point of the rectangle (number) */,
	'boundingBox.bottom' DOUBLE /* y position of bottom right point of the rectangle (number) */
);
