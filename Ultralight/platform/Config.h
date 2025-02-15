///
/// @file Config.h
///
/// @brief The header for the Config struct.
///
/// @author
///
/// This file is a part of Ultralight, a next-generation HTML renderer.
///
/// Website: <http://ultralig.ht>
///
/// Copyright (C) 2021 Ultralight, Inc. All rights reserved.
///
#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/String.h>

namespace ultralight {

///
/// The winding order for front-facing triangles. (Only used when the GPU renderer is used)
///
enum class UExport FaceWinding : uint8_t {
  ///
  /// Clockwise Winding (Direct3D, etc.)
  ///
  Clockwise,

  ///
  /// Counter-Clockwise Winding (OpenGL, etc.)
  ///
  CounterClockwise,
};

enum class UExport FontHinting : uint8_t {
  ///
  /// Lighter hinting algorithm-- glyphs are slightly fuzzier but better resemble their original
  /// shape. This is achieved by snapping glyphs to the pixel grid only vertically which better
  /// preserves inter-glyph spacing.
  ///
  Smooth,

  ///
  /// Default hinting algorithm-- offers a good balance between sharpness and shape at smaller font
  /// sizes.
  ///
  Normal,

  ///
  /// Strongest hinting algorithm-- outputs only black/white glyphs. The result is usually
  /// unpleasant if the underlying TTF does not contain hints for this type of rendering.
  ///
  Monochrome,
};

///
/// @brief  Configuration settings for Ultralight.
///
/// This is intended to be implemented by users and defined before creating the Renderer. @see
/// Platform::set_config.
///
struct UExport Config {
  ///
  /// The file path to a writable directory that will be used to store cookies, cached resources,
  /// and other persistent data.
  /// 
  /// Files are only written to disk when using a persistent Session (see Renderer::CreateSession).
  ///
  String cache_path;

  ///
  /// The library loads bundled resources (eg, cacert.pem and other localized resources) from the
  /// FileSystem API (eg, `file:///resources/cacert.pem`). You can customize the prefix to use when
  /// loading resource URLs by modifying this setting.
  ///
  String resource_path_prefix = "resources/";

  ///
  /// The winding order for front-facing triangles. @see FaceWinding
  ///
  /// Note: This is only used when the GPU renderer is enabled.
  ///
  FaceWinding face_winding = FaceWinding::CounterClockwise;

  ///
  /// The hinting algorithm to use when rendering fonts. @see FontHinting
  ///
  FontHinting font_hinting = FontHinting::Normal;

  ///
  /// The gamma to use when compositing font glyphs, change this value to adjust contrast (Adobe
  /// and Apple prefer 1.8, others may prefer 2.2).
  ///
  double font_gamma = 1.8;

  ///
  /// Default user stylesheet. You should set this to your own custom CSS string to define default
  /// styles for various DOM elements, scrollbars, and platform input widgets.
  ///
  String user_stylesheet;

  ///
  /// Whether or not we should continuously repaint any Views or compositor layers, regardless if
  /// they are dirty or not. This is mainly used to diagnose painting/shader issues.
  ///
  bool force_repaint = false;

  ///
  /// When a CSS animation is active, the amount of time (in seconds) to wait before triggering
  /// another repaint. Default is 60 Hz.
  ///
  double animation_timer_delay = 1.0 / 60.0;

  ///
  /// When a smooth scroll animation is active, the amount of time (in seconds) to wait before
  /// triggering another repaint. Default is 60 Hz.
  ///
  double scroll_timer_delay = 1.0 / 60.0;

  ///
  /// The amount of time (in seconds) to wait before running the recycler (will attempt to return
  /// excess memory back to the system).
  ///
  double recycle_delay = 4.0;

  ///
  /// Size of WebCore's memory cache in bytes.
  ///
  /// @note  You should increase this if you anticipate handling pages with large resources, Safari
  ///        typically uses 128+ MiB for its cache.
  ///
  uint32_t memory_cache_size = 64 * 1024 * 1024;

  ///
  /// Number of pages to keep in the cache. Defaults to 0 (none).
  ///
  /// @note  Safari typically caches about 5 pages and maintains an on-disk cache to support
  ///        typical web-browsing activities. If you increase this, you should probably increase
  ///        the memory cache size as well.
  ///
  uint32_t page_cache_size = 0;

  ///
  /// JavaScriptCore tries to detect the system's physical RAM size to set reasonable allocation
  /// limits. Set this to anything other than 0 to override the detected value. Size is in bytes.
  ///
  /// This can be used to force JavaScriptCore to be more conservative with its allocation strategy
  /// (at the cost of some performance).
  ///
  uint32_t override_ram_size = 0;

  ///
  /// The minimum size of large VM heaps in JavaScriptCore. Set this to a lower value to make these
  /// heaps start with a smaller initial value.
  ///
  uint32_t min_large_heap_size = 32 * 1024 * 1024;

  ///
  /// The minimum size of small VM heaps in JavaScriptCore. Set this to a lower value to make these
  /// heaps start with a smaller initial value.
  ///
  uint32_t min_small_heap_size = 1 * 1024 * 1024;

  ///
  /// The number of threads to use in the Renderer (for parallel painting on the CPU, etc.).
  /// 
  /// You can set this to a certain number to limit the number of threads to spawn.
  /// 
  /// @note  If this value is 0 (the default), the number of threads will be determined at runtime
  ///        using the following formula:
  /// 
  ///        max(PhysicalProcessorCount() - 1, 1)
  /// 
  uint32_t num_renderer_threads = 0;

  /// 
  /// The max amount of time (in seconds) to allow Renderer::Update to run per call. The library
  /// will attempt to throttle timers and/or reschedule work if this time budget is exceeded.
  ///
  double max_update_time = 1.0 / 100.0;
};

} // namespace ultralight
