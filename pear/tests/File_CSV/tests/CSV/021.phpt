--TEST--
File_CSV Test Case 021: Tabs as separators and no quotes
--FILE--
<?php
// $Id: 021.phpt,v 1.2 2007/05/11 21:49:01 cipri Exp $
/**
 * Test for:
 *  - Tabs as separators and no quotes
 */

require_once 'File/CSV.php';

$file = dirname(__FILE__) . '/021.csv';
$conf = File_CSV::discoverFormat($file);

print "Format:\n";
echo 'fields: ' . $conf['fields'] . "\n";
echo "sep:\n";
File_CSV::_dbgBuff($conf['sep']);
echo "quote:\n";
File_CSV::_dbgBuff($conf['quote']);
print "\n";

$data = array();
while ($res = File_CSV::read($file, $conf)) {
    $data[] = $res;
}

print "Data:\n";
print_r($data);
print "\n";
?>
--EXPECT--
Format:
fields: 4
sep:
buff: (_t_)
quote:
buff: (_NULL_)

Data:
Array
(
    [0] => Array
        (
            [0] => Axxxfs
            [1] => 02xxx0 00xxxxx84 11
            [2] => 10/04/06
            [3] => 2163,53
        )

    [1] => Array
        (
            [0] => 10/04/06
            [1] => VIREMENT RECU TIERS     VIR ACOMPTE PAIEMENT FC 904
            [2] => 11/04/06
            [3] => 700,00
        )

    [2] => Array
        (
            [0] => 10/04/06
            [1] => CHEQUE N° 646
            [2] => 08/04/06
            [3] => -33,61
        )

    [3] => Array
        (
            [0] => 07/04/06
            [1] => REMISE CHEQUES          BORDEREAU 05242
            [2] => 11/04/06
            [3] => 1237,93
        )

    [4] => Array
        (
            [0] => 05/04/06
            [1] => PRELEVEMENT             PL PROVINCE 05.04.0
            [2] => 04/04/06
            [3] => -78,00
        )

    [5] => Array
        (
            [0] => 04/04/06
            [1] => COMMISSION TTC          FACTURE NUMERO 038
            [2] => 10/04/06
            [3] => -29,90
        )

    [6] => Array
        (
            [0] => 27/03/06
            [1] => CHEQUE N° 645
            [2] => 25/03/06
            [3] => -34,01
        )

    [7] => Array
        (
            [0] => 24/03/06
            [1] => CHEQUE N° 614
            [2] => 22/03/06
            [3] => -32,75
        )

    [8] => Array
        (
            [0] => 22/03/06
            [1] => CHEQUE N° 643
            [2] => 20/03/06
            [3] => -273,00
        )

    [9] => Array
        (
            [0] => 21/03/06
            [1] => FACTURE CARTE           DU 190306 TOTAL CART
            [2] => 21/03/06
            [3] => -32,00
        )

    [10] => Array
        (
            [0] => 20/03/06
            [1] => PRELEVEMENT             URSSAF
            [2] => 19/03/06
            [3] => -75,00
        )

    [11] => Array
        (
            [0] => 16/03/06
            [1] => VIRT CPTE A CPTE EMIS   VT 17H18 02
            [2] => 15/03/06
            [3] => -1000,00
        )

    [12] => Array
        (
            [0] => 15/03/06
            [1] => CHEQUE N° 641
            [2] => 13/03/06
            [3] => -100,07
        )

    [13] => Array
        (
            [0] => 14/03/06
            [1] => PRELEVEMENT             TELECOM 06 REF
            [2] => 13/03/06
            [3] => -29,99
        )

    [14] => Array
        (
            [0] => 14/03/06
            [1] => CHEQUE N° 642
            [2] => 12/03/06
            [3] => -30,00
        )

)
