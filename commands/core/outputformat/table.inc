<?php

/**
 * Output formatter 'table'
 *
 * @param $data
 *   The $data parameter is expected to be an array (keys ignored) of
 *   rows; each row, in turn, is an array of key / value pairs.  Every
 *   row is expected to have the same set of keys.  The data is rendered
 *   as a formatted word-wrapped table with rows of data cells aligned in
 *   columns.
 * @param $metadata
 *   'field-labels' - If present, contains an array of key / value pairs
 *     that map from the keys in the row columns to the label for the
 *     column header.
 *   'column-widths' - If present, contains an array of key / value pairs,
 *     where the key is the integer column number, and the value is the
 *     width that column should be formatted to.
 *
 * Code:
 *
 *   return array(
 *     "a" => array("b" => 2, "c" => 3),
 *     "d" => array("b" => 5, "c" => 6)
 *   );
 *
 * Output with --format=table:
 *
 *    b  c
 *    2  3
 *    5  6
 */
class drush_outputformat_table extends drush_outputformat {
  function format($input, $metadata) {
    $field_list = isset($metadata['field-labels']) ? $metadata['field-labels'] : array();
    $widths = array();
    $col = 0;
    foreach($field_list as $key => $label) {
      if (isset($metadata['column-widths'][$key])) {
        $widths[$col] = $metadata['column-widths'][$key];
      }
      ++$col;
    }
    $temp_rows = drush_rows_of_key_value_to_array_table($input, $field_list, $metadata);
    array_shift($temp_rows);
    /*$field_labels = array_key_exists('include-field-labels', $metadata) && $metadata['include-field-labels'];
    if (!$field_labels) {
      array_shift($rows);
    }
    return drush_format_table($rows, $field_labels, $widths);*/
    $field_list = array_values($field_list);
    foreach($temp_rows as $key=>$row) {
      for($i=0;$i<5;$i++) {
        $rows[$key][$field_list[$i]] = $row[$i];
        if($i==0) {
          if ($row[3] =="Enabled") {
            $rows[$key][$field_list[$i]] = "<bold>" . $row[$i] . "</bold>";
          }
        }
        if($i==1) {
          if ($row[3] =="Enabled") {
            $rows[$key][$field_list[$i]] = "<bold>" . $row[$i] . "</bold>";
          }
        }
        if($i==2) {
          if ($row[3] =="Enabled") {
            $rows[$key][$field_list[$i]] = "<bold>" . $row[$i] . "</bold>";
          }
        }
        if($i==4) {
          if ($row[3] =="Enabled") {
            $rows[$key][$field_list[$i]] = "<bold>" . $row[$i] . "</bold>";
          }
        }
        if($i==3) {
          if ($row[$i] =="Enabled") {
            $rows[$key][$field_list[$i]] = "<bold>" . $row[$i] . "</bold>";
          }
        }
      }
    }
    $climate = new League\CLImate\CLImate;
    $climate->extend('Drush\Console\DrushTable');
    //$climate->border('');
    $climate->table($rows);
    //return $rows;
  }
}
