<?php

namespace Drush\Console;

use League\CLImate\TerminalObject\Basic\Table;

class DrushTable extends Table
{
    /**
     * The divider between table cells
     *
     * @var string $column_divider
     */
    protected $column_divider = '  ';
    protected $column_divider_border = ' | ';

    /**
     * The border to divide each row of the table
     *
     * @var string $border
     */
    protected $show_border = FALSE;

    public function __construct(array $data)
    {
        $this->data = $data;
        if ($this->show_border) {
            $this->column_divider = $this->column_divider_border;
        }
    }

    /**
     * Return the built rows
     *
     * @return array
     */
    public function result()
    {
        $this->column_widths = $this->getColumnWidths();
        $this->table_width   = $this->getWidth();
        $this->border        = $this->getBorder();

        $this->buildHeaderRow();

        foreach ($this->data as $key => $columns) {
            $this->rows[] = $this->buildRow($columns);
            if ($this->show_border) {
              $this->rows[] = $this->border;
            }
        }

        return $this->rows;
    }

    /**
     * Check for a header row (if it's an array of associative arrays or objects),
     * if there is one, tack it onto the front of the rows array
     */
    protected function buildHeaderRow()
    {
        $header_row = $this->getHeaderRow();

        if ($header_row) {
            if ($this->show_border) {
                $this->rows[] = $this->border;
            }
            $this->rows[] = $this->buildRow($header_row);

            if ($this->show_border) {
                $this->rows[] = (new Border())->char('=')
                  ->length($this->table_width)
                  ->result();
            }
        } else {
            $this->rows[] = $this->border;
        }
    }
}
