/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: 0.3 alpha */
/* DummyBoundingBoxes_output_ObjectData.sql */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "DummyBoundingBoxes_output_ObjectData";
CREATE TABLE "DummyBoundingBoxes_output_ObjectData"
(
	'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */,
	'configID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of config chain (string) */,
	'id' VARCHAR(32) NOT NULL DEFAULT '' /* object ID (string) */,
	'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */,
	'objectID' VARCHAR(32) NOT NULL DEFAULT '' /* object ID (string) */,
	'detections._idx1' BIGINT /* array index dimension: 1 (array) */,
	'detections.timestamp' BIGINT /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */,
	'detections.confidence' DOUBLE DEFAULT '1' /* confidence of detection [0-1] (number) */,
	'detections.boundingBox.left' DOUBLE /* x position of top left point of the rectangle (number) */,
	'detections.boundingBox.right' DOUBLE /* x position of bottom right point of the rectangle (number) */,
	'detections.boundingBox.top' DOUBLE /* y position of top left point of the rectangle (number) */,
	'detections.boundingBox.bottom' DOUBLE /* y position of bottom right point of the rectangle (number) */,
	'detections.basePoint.x' DOUBLE /* x position of point (number) */,
	'detections.basePoint.y' DOUBLE /* y position of point (number) */
);
