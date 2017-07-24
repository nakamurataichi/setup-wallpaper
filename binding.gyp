{
  "targets": [
    {
      "target_name": "setup_wallpaper",
      "sources": [
        "program.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
