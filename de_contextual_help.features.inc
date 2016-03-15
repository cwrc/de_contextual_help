<?php
/**
 * @file
 * Features hook implementations.
 */

/**
 * Implementation of hook_features_export_options.
 *
 * This hook will alert features of which specific items of this component may
 * be exported. For instances, in this case, we want to make available all the
 * existing items.  If there are no items to be exported, this component will
 * not be made available in the features export page.
 *
 * @return array
 *   A keyed array of items, suitable for use with a FormAPI select or
 *   checkboxes element.
 */
function de_contextual_help_config_features_export_options() {
  $field_types = array (
    'all_rules' => t('All Contextual Help rules.'),
  );
  return $field_types;
}

/**
 * Implementation of hook_features_export.
 *
 * This is a component hook, rather then a module hook, therefore this is the
 * callback from hook_features_api which relates to the specific component we
 * are looking to export. When a specific instance of the component we are
 * looking to export is selected, this will include the necessariy item, plus
 * any dependencies into our export array.
 *
 * @param array $data
 * this is the machine name for the component in question
 * @param array &$export
 * array of all components to be exported
 * @param string $module_name
 * The name of the feature module to be generated.
 * @return array
 * The pipe array of further processors that should be called
 */
function de_contextual_help_config_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['de_contextual_help'] = 'de_contextual_help';

  foreach ($data as $component) {
    $export['features']['de_contextual_help_config'][$component] = $component;
  }
}

/**
 * Implementation of hook_features_export_render.
 *
 * This hook will be invoked in order to export
 * Component hook. The hook should be implemented using the name ot the
 * component, not the module, eg. [component]_features_export() rather than
 * [module]_features_export().
 *
 * Render one or more component objects to code.
 *
 * @param string $module_name
 *   The name of the feature module to be exported.
 * @param array $data
 *   An array of machine name identifiers for the objects to be rendered.
 * @param array $export
 *   The full export array of the current feature being exported. This is only
 *   passed when hook_features_export_render() is invoked for an actual feature
 *   update or recreate, not during state checks or other operations.
 * @return array
 *   An associative array of rendered PHP code where the key is the name of the
 *   hook that should wrap the PHP code. The hook should not include the name
 *   of the module, e.g. the key for `hook_example` should simply be `example`.
 */
function de_contextual_help_config_features_export_render($module_name, $data, $export = NULL) {
  $code = array ();
  if (in_array('all_rules', $data)) {
    $code = contextual_help_rules();
  }

  $code = '  return ' . features_var_export($code) . ';';
  return array ('de_contextual_help_config_features_default_settings' => $code);
}

/**
 * Implementation of hook_features_revert().
 */
function de_contextual_help_config_features_revert($module) {
  de_contextual_help_config_features_rebuild($module);
}

/**
 * Implementation of hook_features_rebuild().
 */
function de_contextual_help_config_features_rebuild($module) {
  $items = module_invoke($module, 'de_contextual_help_config_features_default_settings');
  if (!empty($items)) {
    db_delete('contextual_help_rules')
      ->execute();
  }
  //loop over the items we need to recreate
  foreach ($items as $item) {
    $chrule = new stdClass;
    $chrule->url_pattern = $item['url_pattern'];
    $chrule->link_destination = $item['link_destination'];
    $chrule->weight = (int) $item['weight'];
    contextual_help_rule_save($chrule);
  }
}

