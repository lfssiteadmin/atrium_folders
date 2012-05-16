<?php


function theme_folder_toolbar_fieldset($element) {
  $output .= '<div class="left"><div class="inner">';
  $output .= '    <div class="title">'. $element['#title'] .'</div>';
  $output .= '    <div class="description">'. $element['#description'] .'</div>';
  $output .= '</div></div>';
  $output .= '<div class="right"><div class="inner">';
  foreach (element_children($element) as $name) {
  	$output .= drupal_render($element[$name]);
  }
  $output .= '</div></div>';
  return $output;
}

function theme_folder_toolbar_form($form) {

  $output = '';
  $links = array();
  $buttons = array();
  drupal_add_js(drupal_get_path('module', 'atrium_folders') .'/js/atrium_folders_toolbar.js');

  $buttons = $form['buttons'];
  $buttons['#weight'] = 1000;
  unset($form['buttons']);
  foreach (element_children($form) as $name) {
    if ($form[$name]['#theme'] == 'folder_toolbar_fieldset') {
      $links[$name]['title'] = $form[$name]['#title'];
      $links[$name]['href'] = $_GET['q'];
      $links[$name]['fragment'] = $name;
      $links[$name]['attributes'] = array('class' => 'folder-toolbar-link');

      $form[$name]['#attributes'] = array('id' => $name, 'class' => 'folder-toolbar-fieldset fieldset titled');
      unset($buttons['preview']);
      unset($buttons['preview_changes']);
      $form[$name]['buttons'] = $buttons;
      $form[$name]['buttons']['#prefix'] = '<div class="buttons" style="display: block;">';
      $form[$name]['buttons']['#suffix'] = '</div>';
      $output .= drupal_render($form[$name]);
    }
    else {
      $form[$name]['#attributes'] = array('style' => 'display: none;');
      $output .= drupal_render($form[$name]);
    }
  }

  return '<div class="buttons">'. theme('links', $links) .'</div>' . $output;
}

/**
 * Theme textfields element
 */
function theme_textfields($element) {
  return $element['#children'];
}

/**
 * Theme list of files
 *
 * $files: array of associative arrays, each including:
 *   filename, filepath, filemime, filesize, description
 */
function theme_atrium_folders_file_list($files) {
  $header = '';
  $rows = array();
  foreach ($files as $file) {
    $row = array();
    $row['file'] = l($file['filename'], file_create_url($file['filename']));
    $rows[] = $row;
  }
  $table = theme('table', $header, $rows);
  $description = '<p>Files uploaded to group folders and other group content.</p>';
  return $description . $table;
}
