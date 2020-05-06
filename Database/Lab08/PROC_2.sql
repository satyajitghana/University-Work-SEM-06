DROP procedure IF EXISTS GetPhoneNo;

DELIMITER //

CREATE procedure GetPhoneNo ( IN name_value VARCHAR(20) )

BEGIN

    SELECT Phone, Name from OFFICES WHERE Name = name_value ;

END; //

DELIMITER ;

SET @NAME = 'Satyajit' ; 

CALL GetPhoneNo(@NAME) ;