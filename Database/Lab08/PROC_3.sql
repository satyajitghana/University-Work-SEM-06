DROP procedure IF EXISTS GetOffice ;

DELIMITER //

CREATE procedure GetOffice ( IN country_value VARCHAR(20) )

BEGIN

    SELECT Country, COUNT(*) as Count FROM OFFICES WHERE Country = country_value ;

END; //

DELIMITER ;

SET @COUNTRY = 'India' ; 

CALL GetOffice(@COUNTRY) ;