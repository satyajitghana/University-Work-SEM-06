DROP procedure IF EXISTS IncreaseCount;

DELIMITER //

CREATE procedure IncreaseCount ( INOUT ending_value INT, IN inc_value INT )

BEGIN

    SET ending_value = ending_value + inc_value ;

END; //

DELIMITER ;

SET @END_VAL = 15 ; 

CALL IncreaseCount(@END_VAL, 10) ;

SELECT @END_VAL ;