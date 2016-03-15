<?php
/**
 * @file
 * de_contextual_help.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function de_contextual_help_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['de_contextual_help-contextual_help_link'] = array(
    'cache' => 4,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'contextual_help_link',
    'module' => 'de_contextual_help',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'de_theme' => array(
        'region' => 'masthead',
        'status' => 1,
        'theme' => 'de_theme',
        'weight' => 6,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
