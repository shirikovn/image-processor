<div align="center">
  <img src="https://github.com/shirikovn/image-processor/blob/main/.github/assets/image-processor-high-resolution-logo-transparent.png" alt="image-processor" width="400">
  <h3 align="center">Simple filters for your bitmap images.</h3>
</div>


## About the project
| original image     | gaussian blur      |
|------------|-------------|
|![MARBLES](https://github.com/shirikovn/image-processor/assets/91596934/d9700c5f-94df-425a-aa1e-80697427cb6f)|![Product Name Screen Shot](.github/assets/marbels.png)|

This project was made as final project for C++ course in HSE.

Works only with 24-bit bmp no compression.

## Usage

Example of standart usage:

```sh
input_path output_path -sharp -blur 7
```

You can use as many filters as you want.

## List of available filters and their params:

-crop {wigth} {hieght}: crop image to given size

-neg: negative image

-sharp: make image sharper

-gs: convert image to grey shades

-edge: {param}: detect edges (pixels that are bigger than param[0-1])

-blur: {param}: Gaussian blur with sigma = param

-chess-br {koef} {size}: Make chess-like brightning with size of cell = size

## How to build

Build as standart CMake project.
